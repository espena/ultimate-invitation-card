#include <memory.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/adc.h"
#include "driver/gpio.h"
#include "driver/gptimer.h"
#include "esp_log.h"
#include "cuttable_wire_watcher.hpp"
#include "playbook_item.hpp"

using namespace espena::components;

const char* cuttable_wire_watcher::m_component_name = "cuttable_wire_watcher";
const esp_event_base_t cuttable_wire_watcher::m_event_base = "CUTTABLE_WIRE_WATCHER_EVENT";

cuttable_wire_watcher::cuttable_wire_watcher() : m_sample_counter( 0 ),
                                                 m_cutted_wire( cuttable_wire::none ) {
  
  m_message_queue = xQueueCreate( 50, sizeof( cuttable_wire_watcher_task_queue_item ) );
  
  memset( &m_task_params, 0x00, sizeof( cuttable_wire_watcher_task_params ) );
  m_task_params.instance = this;

  m_task_params.stack_buffer = ( StackType_t * ) heap_caps_malloc( m_component_stack_size,
                                                                   MALLOC_CAP_SPIRAM );
  xTaskCreateStatic( &cuttable_wire_watcher::task_loop,
                     m_component_name,
                     m_component_stack_size,
                     &m_task_params,
                     1,
                     m_task_params.stack_buffer,
                     &m_task_params.task_buffer ); 

  m_timer = NULL;

  // No pullups on I34 and IO35 - so we utilize the
  // A/D converter to figure out the I/O levels

  adc1_config_width( ADC_WIDTH_BIT_12 );
  adc1_config_channel_atten( ADC1_CHANNEL_6, ADC_ATTEN_DB_0 );
  adc1_config_channel_atten( ADC1_CHANNEL_7, ADC_ATTEN_DB_0 );

}

::espena::cuttable_wire cuttable_wire_watcher::cutted_wire() {
  return m_cutted_wire;
}

void cuttable_wire_watcher::set_event_loop_handle( esp_event_loop_handle_t event_loop_handle ) {
  m_event_dispatcher.set_event_loop_handle( event_loop_handle );
}

void cuttable_wire_watcher::add_event_listener( cuttable_wire_watcher::event event_id,
                                        esp_event_handler_t event_handler )
{
  m_event_dispatcher.add_event_listener( m_event_base,
                                         static_cast<int32_t>( event_id ),
                                         event_handler );
}

bool cuttable_wire_watcher::on_alarm( gptimer_handle_t timer,
                              const gptimer_alarm_event_data_t *edata,
                              void *user_ctx )
{
  cuttable_wire_watcher *inst = static_cast<cuttable_wire_watcher *>( user_ctx );
  cuttable_wire_watcher_task_queue_item item;
  memset( &item, 0x00, sizeof( cuttable_wire_watcher_task_queue_item ) );
  item.message = cuttable_wire_watcher_task_message::check_wires;
  item.arg = nullptr;
  BaseType_t high_task_awoken = pdFALSE;
  xQueueSendFromISR( inst->m_message_queue, &item, &high_task_awoken );
  return true;
}

void cuttable_wire_watcher::check_wires() {
  int red_wire = adc1_get_raw( ADC1_CHANNEL_6 );    // GPIO34
  int green_wire = adc1_get_raw( ADC1_CHANNEL_7 );  // GPIO35
  if( green_wire > 5 || red_wire > 5 ) { // Usually 0 when closed, but we need a little tolerance
    // One of the wires was cut
    m_cutted_wire = ( red_wire > 5 ? espena::cuttable_wire::red : espena::cuttable_wire::green );
    if( m_sample_counter > 5 ) { // We need to know if the wire was cut just now, or from before boot
      ESP_LOGI( m_component_name, "Wire was just cut" );
      m_event_dispatcher.dispatch( m_event_base, static_cast<int32_t>( event::wire_recently_cut ), static_cast<void *>( &m_cutted_wire ), sizeof( m_cutted_wire ) );
    }
    else {
      ESP_LOGI( m_component_name, "Wire previously cut" );
      m_event_dispatcher.dispatch( m_event_base, static_cast<int32_t>( event::wire_previously_cut ), static_cast<void *>( &m_cutted_wire ), sizeof( m_cutted_wire ) );
    }
    stop_sync();
  }
  m_sample_counter++;
}

void cuttable_wire_watcher::task_loop( void *arg ) {
  cuttable_wire_watcher_task_params *params = static_cast<cuttable_wire_watcher_task_params *>( arg );
  cuttable_wire_watcher *inst = params->instance;
  cuttable_wire_watcher_task_queue_item item;
  memset( &item, 0x00, sizeof( cuttable_wire_watcher_task_queue_item ) );
  while( 1 ) {
    if( xQueueReceive( inst->m_message_queue, &item, 10 ) ) {
      inst->on_message( item.message );
    }
  }
}

void cuttable_wire_watcher::on_message( cuttable_wire_watcher_task_message msg ) {
  switch( msg ) {
    case cuttable_wire_watcher_task_message::start:
      start_sync();
      break;
    case cuttable_wire_watcher_task_message::check_wires:
      check_wires();
      break;
    case cuttable_wire_watcher_task_message::stop:
      stop_sync();
      break;
  }
}

void cuttable_wire_watcher::start_sync() {
  gptimer_alarm_config_t alarm_config;
  memset( &alarm_config, 0x00, sizeof( gptimer_alarm_config_t ) );
  alarm_config.alarm_count = 2000000;
  alarm_config.flags.auto_reload_on_alarm = 1;
  gptimer_event_callbacks_t cbs;
  cbs.on_alarm = &on_alarm;
  gptimer_config_t timer_config = {
    .clk_src = GPTIMER_CLK_SRC_DEFAULT,
    .direction = GPTIMER_COUNT_UP,
    .resolution_hz = 1 * 1000 * 1000,
    .flags = {
      .intr_shared = 1
    }
  };
  gptimer_new_timer( &timer_config, &m_timer );
  gptimer_set_alarm_action( m_timer, &alarm_config );
  gptimer_register_event_callbacks( m_timer, &cbs, this );
  vTaskDelay( 100 / portTICK_PERIOD_MS ); // < Wait for A/D converter to stabilize
  gptimer_enable( m_timer );
  gptimer_start( m_timer );
}

void cuttable_wire_watcher::stop_sync() {
  gptimer_stop( m_timer );
}

void cuttable_wire_watcher::start() {
  cuttable_wire_watcher_task_queue_item item;
  memset( &item, 0x00, sizeof( cuttable_wire_watcher_task_queue_item ) );
  item.message = cuttable_wire_watcher_task_message::start;
  item.arg = nullptr;
  xQueueSend( m_message_queue, &item, portMAX_DELAY );
}

void cuttable_wire_watcher::stop() {
  cuttable_wire_watcher_task_queue_item item;
  memset( &item, 0x00, sizeof( cuttable_wire_watcher_task_queue_item ) );
  item.message = cuttable_wire_watcher_task_message::stop;
  item.arg = nullptr;
  xQueueSend( m_message_queue, &item, portMAX_DELAY );
}

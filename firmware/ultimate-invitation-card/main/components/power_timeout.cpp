#include <memory.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gptimer.h"
#include "esp_log.h"
#include "power_timeout.hpp"

using namespace espena::components;

const char* power_timeout::m_component_name = "power_timeout";
const esp_event_base_t power_timeout::m_event_base = "POWER_TIMEOUT_EVENT";

power_timeout::power_timeout() {
  m_message_queue = xQueueCreate( 2, sizeof( power_timeout_task_queue_item ) );
  memset( &m_task_params, 0x00, sizeof( power_timeout_task_params ) );
  m_task_params.instance = this;

  m_task_params.stack_buffer = ( StackType_t * ) heap_caps_malloc( m_component_stack_size,
                                                                   MALLOC_CAP_SPIRAM );
  xTaskCreateStatic( &power_timeout::task_loop,
                     m_component_name,
                     m_component_stack_size,
                     &m_task_params,
                     2,
                     m_task_params.stack_buffer,
                     &m_task_params.task_buffer ); 

  m_timer = NULL;
  gptimer_alarm_config_t alarm_config;
  memset( &alarm_config, 0x00, sizeof( gptimer_alarm_config_t ) );
  alarm_config.alarm_count = 1000000 * 60 * m_timeout_minutes;
  alarm_config.flags.auto_reload_on_alarm = 0;
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
  gptimer_enable( m_timer );
  gptimer_start( m_timer );
}

void power_timeout::set_event_loop_handle( esp_event_loop_handle_t event_loop_handle ) {
  m_event_dispatcher.set_event_loop_handle( event_loop_handle );
}

void power_timeout::add_event_listener( power_timeout::event event_id,
                                        esp_event_handler_t event_handler )
{
  m_event_dispatcher.add_event_listener( m_event_base,
                                         static_cast<int32_t>( event_id ),
                                         event_handler );
}

bool power_timeout::on_alarm( gptimer_handle_t timer,
                              const gptimer_alarm_event_data_t *edata,
                              void *user_ctx )
{
  power_timeout *inst = static_cast<power_timeout *>( user_ctx );
  power_timeout_task_queue_item item;
  memset( &item, 0x00, sizeof( power_timeout_task_queue_item ) );
  item.message = power_timeout_task_message::on_alarm;
  item.arg = nullptr;
  xQueueSend( inst->m_message_queue, &item, portMAX_DELAY );
  return true;
}

void power_timeout::task_loop( void *arg ) {
  power_timeout_task_params *params = static_cast<power_timeout_task_params *>( arg );
  power_timeout *inst = params->instance;
  power_timeout_task_queue_item item;
  memset( &item, 0x00, sizeof( power_timeout_task_queue_item ) );
  while( 1 ) {
    if( xQueueReceive( inst->m_message_queue, &item, 10 ) ) {
      inst->on_message( item.message );
    }
  }
}

void power_timeout::timeout() {
  ESP_LOGI( m_component_name, "Timeout alarm" );
  m_event_dispatcher.dispatch( m_event_base, static_cast<int32_t>( event::timeout ), NULL, 1 );
}

void power_timeout::reset() {
  ESP_LOGI( m_component_name, "Reset timer" );
  power_timeout_task_queue_item item;
  memset( &item, 0x00, sizeof( power_timeout_task_queue_item ) );
  item.message = power_timeout_task_message::reset_timer;
  xQueueSend( m_message_queue, &item, portMAX_DELAY );
}

void power_timeout::on_message( power_timeout_task_message msg ) {
  switch( msg ) {
    case power_timeout_task_message::on_alarm:
      timeout();
      break;
    case power_timeout_task_message::reset_timer:
      gptimer_set_raw_count( m_timer, 0 );
      break;
  }
}

#include <vector>
#include "memory.h"
#include "driver/gpio.h"
#include "driver/gptimer.h"
#include "driver/ledc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"
#include "pwm.hpp"

using namespace espena::components;

int pwm::m_pwm_count = 0;
const char* pwm::m_component_name = "pwm";
QueueHandle_t pwm::m_message_queue = xQueueCreate( 5, sizeof( pwm_task_queue_item ) );
pwm::pwm_task_params pwm::m_task_params;
std::vector<pwm *> pwm::m_instances;
gptimer_handle_t pwm::m_pwm_timer = nullptr;
bool pwm::m_breathe_out = false;

pwm::pwm( gpio_num_t gpio_num, std::string group_name ) : m_gpio_num( gpio_num ),
                                                          m_group_name( group_name )
{
  m_ledc_channel = static_cast<ledc_channel_t>( m_pwm_count++ );
  if( m_ledc_channel >= LEDC_CHANNEL_MAX ) {
    ESP_LOGE( m_component_name, "Too many PWM items" );
  }
  else {
    if( m_pwm_count == 1 ) {
      init_static_ledc();
      init_static_pwm_timer();
    }
    init_pwm_channel();
    init_pwm_task();
    m_instances.push_back( this );
  }  
}

void pwm::init_static_ledc() {
  ledc_timer_config_t ledc_timer = {
    .speed_mode = LEDC_LOW_SPEED_MODE,
    .duty_resolution = LEDC_TIMER_13_BIT,
    .timer_num = LEDC_TIMER_0,
    .freq_hz = 5000,
    .clk_cfg = LEDC_AUTO_CLK,
    .deconfigure = false
  };
  ledc_timer_config( &ledc_timer );
  ledc_fade_func_install( 0 );
}

void pwm::init_static_pwm_timer() {
  gptimer_config_t timer;
  memset( &timer, 0x00, sizeof( gptimer_config_t ) );
  timer.clk_src = GPTIMER_CLK_SRC_DEFAULT;
  timer.direction = GPTIMER_COUNT_UP;
  timer.resolution_hz = 1000000;
  gptimer_new_timer( &timer, &m_pwm_timer );
  gptimer_alarm_config_t alarm_config;
  memset( &alarm_config, 0x00, sizeof( gptimer_alarm_config_t ) );
  alarm_config.alarm_count = 1001000;
  alarm_config.flags.auto_reload_on_alarm = 1;
  gptimer_set_alarm_action( m_pwm_timer, &alarm_config );
  gptimer_event_callbacks_t callbacks;
  memset( &callbacks, 0x00, sizeof( gptimer_event_callbacks_t ) );
  callbacks.on_alarm = on_pwm_timer;
  gptimer_register_event_callbacks( m_pwm_timer, &callbacks, this );
  gptimer_enable( m_pwm_timer );
  gptimer_start( m_pwm_timer );
}

void pwm::init_pwm_channel() {
  ledc_channel_config_t ledc_channel = {
    .gpio_num = m_gpio_num,
    .speed_mode = LEDC_LOW_SPEED_MODE,
    .channel = m_ledc_channel,
    .intr_type = LEDC_INTR_DISABLE,
    .timer_sel = LEDC_TIMER_0,
    .duty = 0,
    .hpoint = 0,
    .flags = {
      .output_invert = 0
    }
  };
  ledc_channel_config( &ledc_channel );
}

void pwm::init_pwm_task() {
    memset( &m_task_params, 0x00, sizeof( pwm_task_params ) );
    m_task_params.instance = this;
    xTaskCreate( &pwm::task_loop,
                m_component_name,
                m_component_stack_size,
                &m_task_params,
                1,
                &m_task_params.task_handle );
}

bool pwm::on_pwm_timer( gptimer_handle_t timer,
                        const gptimer_alarm_event_data_t *edata,
                        void *user_ctx )
{
  
  for( auto pwm = m_instances.begin(); pwm != m_instances.end(); pwm++ ) {
    if( ( *pwm )->m_breathe ) {
      ledc_set_fade_with_time( LEDC_LOW_SPEED_MODE,
                               ( *pwm )->m_ledc_channel,
                               m_breathe_out ?    0 : 1600,
                               m_breathe_out ? 800 : 400 );
      ledc_fade_start( LEDC_LOW_SPEED_MODE,
                       ( *pwm )->m_ledc_channel,
                       LEDC_FADE_NO_WAIT );
    }
  }
  m_breathe_out = !m_breathe_out;
  return true;
}

void pwm::task_loop( void *arg ) {
  pwm_task_params *params = static_cast<pwm_task_params *>( arg );
  pwm_task_queue_item item;
  memset( &item, 0x00, sizeof( pwm_task_queue_item ) );
  while( 1 ) {
    if( xQueueReceive( m_message_queue, &item, 10 ) ) {
      ::espena::components::pwm *inst = static_cast<::espena::components::pwm *>( item.arg );
      int beep_duration_ms = 75;
      switch( item.message ) {
        case pwm_task_message::on:
          ledc_set_duty( LEDC_LOW_SPEED_MODE, inst->m_ledc_channel, ( uint32_t ) 8191 * 25 / 100 );
          ledc_update_duty( LEDC_LOW_SPEED_MODE, inst->m_ledc_channel );
          break;
        case pwm_task_message::off:
          ledc_set_duty( LEDC_LOW_SPEED_MODE, inst->m_ledc_channel, 0 );
          ledc_update_duty( LEDC_LOW_SPEED_MODE, inst->m_ledc_channel );
          break;
        case pwm_task_message::breathe:
          inst->m_breathe = true;
          break;
        case pwm_task_message::stop_breathe:
          inst->m_breathe = false;
          inst->off();
          break;
        case pwm_task_message::timed:
          vTaskDelay( item.delay / portTICK_PERIOD_MS );
          inst->on();
          vTaskDelay( item.duration / portTICK_PERIOD_MS );
          inst->off();
          break;
        case pwm_task_message::beeeep:
          beep_duration_ms *= 10;
          // fallthru
        case pwm_task_message::beeep:
          beep_duration_ms *= 5;
          // fallthru
        case pwm_task_message::beep:
          ledc_set_duty( LEDC_LOW_SPEED_MODE, inst->m_ledc_channel, ( uint32_t ) 8191 * 25 / 100 );
          ledc_update_duty( LEDC_LOW_SPEED_MODE, inst->m_ledc_channel );
          vTaskDelay( beep_duration_ms / portTICK_PERIOD_MS );
          ledc_set_duty( LEDC_LOW_SPEED_MODE, inst->m_ledc_channel, ( uint32_t ) 0 );
          ledc_update_duty( LEDC_LOW_SPEED_MODE, inst->m_ledc_channel );
          break;
      }
    }
  }
}

void pwm::msg_queue_put( pwm_task_message msg ) {
  pwm_task_queue_item item;
  memset( &item, 0x00, sizeof( pwm_task_queue_item ) );
  item.message = msg;
  item.arg = this;
  xQueueSend( m_message_queue, &item, portMAX_DELAY );
}

void pwm::breathe() {
  msg_queue_put( pwm_task_message::breathe );
}

void pwm::breathe( std::string group_name ) {
  for( auto pwm = m_instances.begin(); pwm != m_instances.end(); pwm++ ) {
    if( ( *pwm )->m_group_name == group_name ) {
      ( *pwm )->breathe();
    }
  }
}

void pwm::stop_breathe() {
  msg_queue_put( pwm_task_message::stop_breathe );
}

void pwm::stop_breathe( std::string group_name ) {
  for( auto pwm = m_instances.begin(); pwm != m_instances.end(); pwm++ ) {
    if( ( *pwm )->m_group_name == group_name ) {
      ( *pwm )->stop_breathe();
    }
  }
}

void pwm::on( int brightness ) {
  msg_queue_put( pwm_task_message::on );
}

void pwm::on() {
  on( 100 );
}

void pwm::off() {
  msg_queue_put( pwm_task_message::off );
}

void pwm::timed( int delay, int duration ) {
  pwm_task_queue_item item;
  memset( &item, 0x00, sizeof( pwm_task_queue_item ) );
  item.message = pwm_task_message::timed;
  item.arg = this;
  item.delay = delay;
  item.duration = duration;
  xQueueSend( m_message_queue, &item, portMAX_DELAY );
}

void pwm::beep() {
  msg_queue_put( pwm_task_message::beep );
}

void pwm::beeep() {
  msg_queue_put( pwm_task_message::beeep );
}

void pwm::beeeep() {
  msg_queue_put( pwm_task_message::beeeep );
}


#include <vector>
#include <memory.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <driver/gpio.h>
#include <esp_log.h>
#include <esp_event.h>
#include "i_display.hpp"
#include "playbook.hpp"

using namespace espena::components;

const char* playbook::m_component_name = "playbook";
const esp_event_base_t playbook::m_event_base = "PLAYBOOK_EVENT";

playbook::playbook( i_display *display, const char *name ) : m_display( display ),
                                                             m_name( name ),
                                                             m_reset_flag( false )
{
  m_message_queue = xQueueCreate( 10, sizeof( playbook_task_queue_item ) );
  m_task_params.instance = this;

  m_task_params.stack_buffer = ( StackType_t * ) heap_caps_malloc( m_component_stack_size,
                                                                   MALLOC_CAP_SPIRAM );

  xTaskCreateStatic( &playbook::task_loop,
                     m_component_name,
                     m_component_stack_size,
                     &m_task_params,
                     2,
                     m_task_params.stack_buffer,
                     &m_task_params.task_buffer ); 
}

void playbook::task_loop( void *arg ) {
  playbook_task_params *params = static_cast<playbook_task_params *>( arg );
  playbook *inst = params->instance;
  playbook_task_queue_item item;
  memset( &item, 0x00, sizeof( playbook_task_queue_item ) );
  while( 1 ) {
    if( xQueueReceive( inst->m_message_queue, &item, 10 ) ) {
      inst->on_message( item.message, item.arg );
    }
  }
}

void playbook::set_event_loop_handle( esp_event_loop_handle_t event_loop_handle ) {
  m_event_dispatcher.set_event_loop_handle( event_loop_handle );
}

void playbook::add_event_listener( ::espena::components::playbook::event event_id,
                                   esp_event_handler_t event_handler )
{
  m_event_dispatcher.add_event_listener( m_event_base,
                                         static_cast<int32_t>( event_id ),
                                         event_handler );
}

void playbook::remove_event_listener( esp_event_handler_t event_handler )
{
  m_event_dispatcher.remove_event_listener( event_handler );
}

::espena::menu_key playbook::readkey() {
  
  
  struct meny_gpio_key_map {
    gpio_num_t gpio;
    ::espena::menu_key key;
  } m[] = {
    { GPIO_NUM_26, ::espena::menu_key::A },
    { GPIO_NUM_14, ::espena::menu_key::B },
    { GPIO_NUM_22, ::espena::menu_key::C },
    { GPIO_NUM_13, ::espena::menu_key::D }
  };

  while( m_reset_flag == false ) {
    for( auto i = 0; i < 4; i++ ) {
      if( gpio_get_level( m[ i ].gpio ) == 0 ) {
        while( gpio_get_level( m[ i ].gpio ) == 0 ) {
          vTaskDelay( 10 );
        }
        return m[ i ].key;
      }
    }
    vTaskDelay( 1 );
  }
  return ::espena::menu_key::NONE;
}

void playbook::play( ::espena::playbook_item item ) {

  ESP_LOGI( m_component_name, "Play item from %s", m_name.c_str() );

  menu_key key = menu_key::NONE;
  ::espena::menu_select menu_selection;
  m_event_dispatcher.dispatch( m_event_base,
                              static_cast<int32_t>( event::cuttable_wire ),
                              &item.params.que_points[ 0 ].wire,
                              sizeof( item.params.que_points[ 0 ].wire ) );
  if( item.params.beep > 0 ) {
    m_event_dispatcher.dispatch( m_event_base,
                                static_cast<int32_t>( event::beep ),
                                &item.params.beep,
                                sizeof( item.params.beep ) );
  }
  switch( item.type ) {
    case ::espena::playbook_item_type::roll:
      ESP_LOGI( m_component_name, "Display roll text" );
      m_display->roll_text( item.buf, item.params.line_count, item.params.que_points );
      vTaskDelay( item.params.delay_ms / portTICK_PERIOD_MS );
      break;
    case ::espena::playbook_item_type::text:
      ESP_LOGI( m_component_name, "Display text" );
      m_display->write_text( item.buf );
      vTaskDelay( item.params.delay_ms / portTICK_PERIOD_MS );
      break;
    case ::espena::playbook_item_type::menu:
      ESP_LOGI( m_component_name, "Display menu" );
      m_display->write_text( item.buf );
      ESP_LOGI( m_component_name, "Fire prompt-event" );
      m_event_dispatcher.dispatch( m_event_base,
                                   static_cast<int32_t>( event::menu_prompt ),
                                   &item,
                                   sizeof( ::espena::playbook_item ) );
      ESP_LOGI( m_component_name, "Block on readkey" );
      do{
        key = readkey();
      } while( m_reset_flag == false && item.params.event[ key ] == ::espena::menu_select::none );
      ESP_LOGI( m_component_name, "Resume after readkey" );
      if( key != ::espena::menu_key::NONE ) {
        menu_selection = item.params.event[ key ];
        m_event_dispatcher.dispatch( m_event_base,
                                    static_cast<int32_t>( event::menu_select ),
                                    &menu_selection,
                                    sizeof( ::espena::menu_select ) );        
      }
      break;
    case ::espena::playbook_item_type::image:
      ESP_LOGI( m_component_name, "Display image" );
      m_display->draw_image( item.buf );
      if( item.params.delay_ms > 0 ) {
        vTaskDelay( item.params.delay_ms / portTICK_PERIOD_MS );
      }
      if( item.params.event[ ::espena::menu_key::A ] != ::espena::menu_select::none ||
          item.params.event[ ::espena::menu_key::B ] != ::espena::menu_select::none || 
          item.params.event[ ::espena::menu_key::C ] != ::espena::menu_select::none ||
          item.params.event[ ::espena::menu_key::D ] != ::espena::menu_select::none )
      {
        ESP_LOGI( m_component_name, "Fire prompt-event" );
        m_event_dispatcher.dispatch( m_event_base,
                                    static_cast<int32_t>( event::menu_prompt ),
                                    &item,
                                    sizeof( ::espena::playbook_item ) );
        ::espena::menu_select menu_selection = ::espena::menu_select::none;
        do{
          key = readkey();
        } while( m_reset_flag == false && item.params.event[ key ] == ::espena::menu_select::none );
        if( m_reset_flag == false ) {
          menu_selection = item.params.event[ key ];
          m_event_dispatcher.dispatch( m_event_base, 
                                      static_cast<int32_t>( event::menu_select ),
                                      &menu_selection,
                                      sizeof( ::espena::menu_select ) );
        }
      }
      break;
    case ::espena::playbook_item_type::await:
      ESP_LOGI( m_component_name, "Display text and await" );
      m_display->write_text( item.buf );
      m_display->delay( item.params.delay_ms );
      m_await = true;
      while( m_reset_flag == false && m_await ) {
        vTaskDelay( 10 );
      }
      break;
    case ::espena::playbook_item_type::transition:
      ESP_LOGI( m_component_name, "Run transition" );
      m_display->transition(
        item.buf,
        item.params.tween.frame_begin,
        item.params.tween.frame_end,
        item.params.tween.delay_ms );
      if( item.params.delay_ms > 0 ) {
        vTaskDelay( item.params.delay_ms / portTICK_PERIOD_MS );
      }
      break;
  }
}

void playbook::enqueue_simple_message( playbook_task_message msg ) {
  playbook_task_queue_item qitem;
  qitem.message = msg;
  qitem.arg = nullptr;
  xQueueSend( m_message_queue, &qitem, portMAX_DELAY ); 
}

void playbook::add( playbook_item item ) {
  playbook_task_queue_item qitem;
  playbook_item *itemcpy = new playbook_item;
  memcpy( itemcpy, &item, sizeof( playbook_item ) );
  qitem.message = playbook_task_message::add_item;
  qitem.arg = static_cast<void *>( itemcpy );
  xQueueSend( m_message_queue, &qitem, portMAX_DELAY ); 
}

void playbook::add_sync( playbook_item *item ) {
  m_rundown.push_back( *item );
}

void playbook::run() {
  enqueue_simple_message( playbook_task_message::run_playbook );
}

void playbook::run_sync() {

  ESP_LOGI( m_component_name, "Running playbook %s", m_name.c_str() );
  ESP_LOGI( m_component_name, "Number of items in rundown: %i", m_rundown.size() );
  ESP_LOGI( m_component_name, "Reset flag before start: %i", m_reset_flag );

  m_reset_flag = false;

  for( auto i = m_rundown.begin(); m_reset_flag == false && i != m_rundown.end(); i++ ) {
    play( *i );
  }

  ESP_LOGI( m_component_name, "Done with rundown for playbook %s", m_name.c_str() );

  m_await = false;

  // Reset LEDs
  m_event_dispatcher.dispatch( m_event_base,
                                static_cast<int32_t>( event::menu_prompt ),
                                nullptr,
                                0 );

  if( m_reset_flag ) {
    m_reset_flag = false;
    m_event_dispatcher.dispatch( m_event_base,
                                  static_cast<int32_t>( event::play_reset ),
                                  this,
                                  sizeof( playbook ) );
  }
  else {
    m_event_dispatcher.dispatch( m_event_base,
                                  static_cast<int32_t>( event::play_finished ),
                                  this,
                                  sizeof( playbook ) );
  }
}

void playbook::reset() {
  while( !m_reset_flag ) {
    m_reset_flag = true;
  }
}

void playbook::resume() {
  while( m_await ) {
    m_await = false;
  }
}

void playbook::on_message( playbook_task_message msg, void *arg ) {
  ::espena::playbook_item *item = nullptr;
  switch( msg ) {
    case playbook_task_message::add_item:
      item = static_cast<::espena::playbook_item *>( arg );
      add_sync( item );
      delete item;
      break;
    case playbook_task_message::run_playbook:
      run_sync();
      break;
  }
}
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <memory>
#include <cstring>
#include <esp_log.h>
#include <driver/gpio.h>

#include "oled_display.hpp"
#include "font8x8_basic.h"
#include "ssd1306.h"
#include "i_font.hpp"
#include "font8x8_basic.h"

using namespace espena;

const char* oled_display::m_component_name = "oled_display";

oled_display::oled_display() {
  std::memset( &m_task_params, 0x00, sizeof( oled_display_task_params ) );
  m_message_queue = xQueueCreate( 5, sizeof( oled_display_task_queue_item ) );
  m_task_params.instance = this;

  m_task_params.stack_buffer = ( StackType_t * ) heap_caps_malloc( m_component_stack_size,
                                                                   MALLOC_CAP_SPIRAM );
  xTaskCreateStatic( &oled_display::task_loop,
                     m_component_name,
                     m_component_stack_size,
                     &m_task_params,
                     2,
                     m_task_params.stack_buffer,
                     &m_task_params.task_buffer ); 
}

void oled_display::task_loop( void *arg ) {
  oled_display_task_params *params = static_cast<oled_display_task_params *>( arg );
  oled_display *_this = params->instance;
  _this->init();
  oled_display_task_queue_item item;
  while( 1 ) {
    vTaskDelay( 1 );
    if( xQueueReceive( _this->m_message_queue, &item, portMAX_DELAY ) ) {
      _this->msg_proc( item.msg, &item );
    }
  }
}

void oled_display::msg_proc( oled_display_task_message msg, oled_display_task_queue_item *item ) {
  switch( msg ) {
    case  oled_display_task_message::write_text:
      {
        ESP_LOGI( m_component_name, "msg_proc -> oled_display_write_text" );
        write_text_message_params * p = static_cast<write_text_message_params *>( item->arg );
        write_text( p );
        delete p;
      }
      break;
    case  oled_display_task_message::roll_text:
      {
        ESP_LOGI( m_component_name, "msg_proc -> oled_display_roll_text" );
        write_text_message_params * p = static_cast<write_text_message_params *>( item->arg );
        roll_text( p );
        delete p;
      }
      break;
    case  oled_display_task_message::draw_image:
      {
        ESP_LOGI( m_component_name, "msg_proc -> oled_display_draw_image" );
        draw_image_message_params * p = static_cast<draw_image_message_params *>( item->arg );
        draw_image( p );
        delete p;
      }
      break;
    case  oled_display_task_message::overlay:
      {
        ESP_LOGI( m_component_name, "msg_proc -> oled_display_overlay" );
        overlay_message_params * p = static_cast<overlay_message_params *>( item->arg );
        overlay( p );
        delete p;
      }
      break;
    case  oled_display_task_message::transition:
      {
        ESP_LOGI( m_component_name, "msg_proc -> oled_display_transition" );
        transition_message_params * p = static_cast<transition_message_params *>( item->arg );
        transition( p );
        delete p;
      }
      break;
    case  oled_display_task_message::delay:
      {
        ESP_LOGI( m_component_name, "msg_proc -> oled_display_delay" );
        delay_message_params * p = static_cast<delay_message_params *>( item->arg );
        delay( p );
        delete p;
      }
      break;
    case  oled_display_task_message::clear:
      {
        ESP_LOGI( m_component_name, "msg_proc -> oled_display_clear" );
        clear_message_params * p = static_cast<clear_message_params *>( item->arg );
        clear( p );
        delete p;
      }
      break;
    default:
      ESP_LOGW( m_component_name, "Unhandled task message" );
  }
}

void oled_display::init() {
  i2c_master_init( &m_task_params.device, 4, 5, 0 );
  ssd1306_init( &m_task_params.device, 128, 64 );
  ssd1306_contrast( &m_task_params.device, 0xff );
}

void oled_display::write_text( const uint8_t *buf ) {
  ESP_LOGI( m_component_name, "write_text was requested..." );
  write_text_message_params *p = new write_text_message_params;
  p->buf = buf;
  p->width = m_width;
  p->height = m_height;
  oled_display_task_queue_item item = {
    msg: oled_display_task_message::write_text,
    arg: p
  };
  xQueueSend( m_message_queue, &item, 1 );
}

void oled_display::write_text( write_text_message_params *params ) {
  ESP_LOGI( m_component_name, "write_text was queued and called!" );
  for( int i = 0; i < 8; i++ ) {
    ssd1306_display_text( &m_task_params.device, i, ( const char * ) ( params->buf + ( i * 17 ) ), 16, false );
  }
}

void oled_display::roll_text( const uint8_t *buf, unsigned int line_count, que_point que_points[ 4 ] ) {
  ESP_LOGI( m_component_name, "roll_text was requested..." );
  write_text_message_params *p = new write_text_message_params;
  p->buf = buf;
  p->width = m_width;
  p->height = m_height;
  p->line_count = line_count;
  memcpy( p->que_points, que_points, sizeof( que_point ) * 4 );
  oled_display_task_queue_item item = {
    msg: oled_display_task_message::roll_text,
    arg: p
  };
  xQueueSend( m_message_queue, &item, 1 );
}

void oled_display::roll_text( write_text_message_params *params ) {
  ESP_LOGI( m_component_name, "roll_text was queued and called!" );
  const uint8_t *cur_line = params->buf;
  const uint8_t *eof_line = params->buf + ( params->line_count * 17 );
  const uint8_t *blank_line = ( uint8_t * ) "                ";
  for( int ln = 0; ln < params->line_count - 8; ln++ ) {
    cur_line += 17;
    for( int offset = 0; offset < 8; offset++ ) {
      for( int page = 0; page < 8; page++ ) {
        if( cur_line < eof_line ) {
          const uint8_t *text_below = cur_line + ( ( page + 1 ) * 17 );
          if( text_below > eof_line ) {
            text_below = blank_line;
          }
          ssd1306_display_text_offset( &m_task_params.device,
                                       page,
                                       ( const char * ) cur_line + ( page * 17 ),
                                       16,
                                       false,
                                       offset,
                                       ( const char * ) text_below );
        }
        else {
          ssd1306_display_text_offset( &m_task_params.device, page, ( const char * ) blank_line, 16, false, 0, NULL );
        }
      }
    }
  }
  ESP_LOGI( m_component_name, "roll_text done!" );
}

void oled_display::overlay( const uint8_t *buf ) {
  ESP_LOGI( m_component_name, "overlay was requested..." );
  overlay_message_params *p = new overlay_message_params;
  p->buf = buf;
  p->width = m_width;
  p->height = m_height;
  oled_display_task_queue_item item = {
    msg: oled_display_task_message::overlay,
    arg: p
  };
  xQueueSend( m_message_queue, &item, 1 );
}

void oled_display::overlay( overlay_message_params *params ) {
  ESP_LOGI( m_component_name, "overlay was queued and called!" );
  for( int i = 0; i < 8; i++ ) {
    // TODO: Implement text overlay
  }
}

void oled_display::draw_image( const uint8_t *buf ) {
  ESP_LOGI( m_component_name, "draw_image was requested..." );
  draw_image_message_params *p = new draw_image_message_params;
  p->buf = buf;
  p->width = m_width;
  p->height = m_height;
  oled_display_task_queue_item item = {
    msg: oled_display_task_message::draw_image,
    arg: p
  };
  xQueueSend( m_message_queue, &item, 1 );
}

void oled_display::draw_image( draw_image_message_params *params ) {
  ESP_LOGI( m_component_name, "draw_image was queued and called!" );
  for( int i = 0; i < 8; i++ ) {
    ssd1306_display_image( &m_task_params.device, i, 0, ( params->buf + ( i * 128 ) ), 128 );
  }
}

void oled_display::transition( const uint8_t *buf, int frame_begin, int frame_end, int delay_ms ) {
  ESP_LOGI( m_component_name, "transition was requested..." );
  transition_message_params *p = new transition_message_params;
  p->buf = buf;
  p->frame_begin = frame_begin;
  p->frame_end = frame_end;
  p->delay_ms = delay_ms;
  p->width = m_width;
  p->height = m_height;
  oled_display_task_queue_item item = {
    msg: oled_display_task_message::transition,
    arg: p
  };
  xQueueSend( m_message_queue, &item, 1 );
}

void oled_display::transition( transition_message_params *params ) {
  ESP_LOGI( m_component_name, "transition was queued and called!" );
  for( int f = params->frame_begin; f < params->frame_end; f++ ) {
    const uint8_t *tween = *( ( uint8_t ** ) params->buf + f ); // ohloord
    for( int i = 0; i < 8; i++ ) {
      ssd1306_display_image( &m_task_params.device, i, 0, ( tween + ( i * 128 ) ), 128 );
    }
    vTaskDelay( params->delay_ms / portTICK_PERIOD_MS );
  }
}

void oled_display::clear( clear_message_params *params ) {
  ssd1306_clear_screen( &m_task_params.device, params->invert );
}

void oled_display::delay( delay_message_params *params ) {
  vTaskDelay( params->ms / portTICK_PERIOD_MS );
}

void oled_display::delay( unsigned int ms ) {
  delay_message_params *p = new delay_message_params;
  p->ms = ms;
  oled_display_task_queue_item item = {
    msg: oled_display_task_message::delay,
    arg: p
  };
  xQueueSend( m_message_queue, &item, 1 );
} 

void oled_display::clear( bool invert ) {
  ESP_LOGI( m_component_name, "clear screen was requested..." );
  clear_message_params *p = new clear_message_params;
  p->invert = invert;
  oled_display_task_queue_item item = {
    msg: oled_display_task_message::clear,
    arg: p
  };
  xQueueSend( m_message_queue, &item, 1 );
}

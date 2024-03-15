#ifndef __oled_display_hpp__
#define __oled_display_hpp__

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <freertos/task.h>
#include <esp_task.h>

#include "playbook_item.hpp"
#include "i_display.hpp"
#include "i_font.hpp"
#include "ssd1306.h"

namespace espena {

  class oled_display : public i_display {

    public:

      static const char* m_component_name;
      static const int m_component_stack_size = 4096;

      static const int m_width = 128;
      static const int m_height = 64;

     private:

      typedef struct oled_display_task_params_struct {
        oled_display *instance;
        StackType_t *stack_buffer;
        StaticTask_t task_buffer;
        SSD1306_t device;
      } oled_display_task_params;

      enum class oled_display_task_message {
        write_text,
        roll_text,
        draw_image,
        overlay,
        transition,
        delay,
        clear
      };

      struct i_message_params {
        virtual ~i_message_params() {}
      };

      struct delay_message_params : i_message_params {
        unsigned int ms;
      };

      struct write_text_message_params : i_message_params {
        const uint8_t *buf;
        const espena::i_font *font;
        unsigned int line_count;
        que_point que_points[ 4 ];
        unsigned int width;
        unsigned int height;
      };

      struct draw_image_message_params : i_message_params {
        const uint8_t *buf;
        unsigned int width;
        unsigned int height;
      };

      struct overlay_message_params : i_message_params {
        const uint8_t *buf;
        unsigned int width;
        unsigned int height;
      };

      struct transition_message_params : i_message_params {
        const uint8_t *buf;
        int frame_begin;
        int frame_end;
        int delay_ms;
        unsigned int width;
        unsigned int height;
      };

      struct clear_message_params : i_message_params {
        bool invert;
      };

      typedef struct oled_display_task_queue_item_struct {
        oled_display_task_message msg;
        void *arg;
      } oled_display_task_queue_item;

      QueueHandle_t m_message_queue;
      oled_display_task_params m_task_params;

      void init();

      void write_text( write_text_message_params *params );
      void roll_text( write_text_message_params *params );
      void draw_image( draw_image_message_params *params );
      void overlay( overlay_message_params *params );
      void transition( transition_message_params *params );
      void delay( delay_message_params *params );
      void clear( clear_message_params *params );

    public:
      
      // Constructor
      oled_display();
      
      // Main task loop
      static void task_loop( void *arg );

      // Message handler
      void msg_proc( oled_display_task_message msg, oled_display_task_queue_item *item );

      // Write text
      void write_text( const uint8_t *buf );

      // Write rolling text
      void roll_text( const uint8_t *buf, unsigned int line_count, que_point que_points[ 4 ] );

      // Write text
      void overlay( const uint8_t *buf );

      // Draw image
      void draw_image( const uint8_t *buf );

      // Play transition
      void transition( const uint8_t *buf, int frame_begin, int frame_end, int delay_ms );

      // Delay
      void delay( unsigned int ms );

      // Clear display
      void clear( bool invert );
      void clear() { clear( false ); }

  }; // class oled_display {

}; // namespace espena

#endif // __oled_display_hpp__
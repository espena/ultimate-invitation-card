#ifndef __playbook_hpp__
#define __playbook_hpp__

#include <vector>
#include <string>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <esp_event.h>
#include "event/event_dispatcher.hpp"
#include "i_display.hpp"
#include "i_playbook.hpp"
#include "playbook_item.hpp"

namespace espena::components {

  class playbook : public i_playbook {

    ::espena::components::event::event_dispatcher m_event_dispatcher;

    i_display *m_display;
    std::string m_name;

    bool m_reset_flag;
    bool m_await;

    QueueHandle_t m_message_queue;
    
    typedef struct playbook_task_params_struct {
      playbook *instance;
      StackType_t *stack_buffer;
      StaticTask_t task_buffer;
    } playbook_task_params;

    playbook_task_params m_task_params;

    enum class playbook_task_message {
      add_item,
      run_playbook
    };

    typedef struct playbook_task_queue_item_struct {
      playbook_task_message message;
      void *arg;
    } playbook_task_queue_item;

    void on_message( playbook_task_message msg, void *arg );

    void enqueue_simple_message( playbook_task_message msg );

    // Sync'ed methods
    void add_sync( ::espena::playbook_item *item );
    void run_sync();

    public:

      std::string get_name() {
        return m_name;
      };

      enum class event {
        base = 0x1000,
        menu_prompt,
        menu_select,
        play_finished,
        play_reset,
        cuttable_wire,
        beep
      };

      static const esp_event_base_t m_event_base;

      playbook( i_display *display, const char *name );

      static void task_loop( void *arg );

      void set_event_loop_handle( esp_event_loop_handle_t esp_event_loop_handle );

      void add_event_listener( ::espena::components::playbook::event,
                               esp_event_handler_t );

      void remove_event_listener( esp_event_handler_t );

      static const char* m_component_name;
      static const int m_component_stack_size = 3072;

      // Async interface
      void add( ::espena::playbook_item item );
      void run();
      void reset();

      std::string name() { return m_name; };

      void resume();

    private:
      std::vector<::espena::playbook_item> m_rundown;

      // Wait for key input (A, B, C, D)
      menu_key readkey();

      // Play a single item
      void play( ::espena::playbook_item item );

  }; // class playbook {

}; // namespace espena

#endif // __playbook_hpp__
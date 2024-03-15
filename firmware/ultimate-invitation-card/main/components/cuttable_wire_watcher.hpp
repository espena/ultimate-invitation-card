#ifndef __cuttable_wire_watcher_hpp__
#define __cuttable_wire_watcher_hpp__

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include "driver/gptimer.h"
#include <esp_event.h>
#include "event/event_dispatcher.hpp"
#include "playbook_item.hpp"

namespace espena::components {

  class cuttable_wire_watcher {

    static const int m_component_stack_size = 4096;
    
    gptimer_handle_t m_timer;
    QueueHandle_t m_message_queue;

    unsigned int m_sample_counter;
    ::espena::cuttable_wire m_cutted_wire;

    ::espena::components::event::event_dispatcher m_event_dispatcher;

    typedef struct cuttable_wire_watcher_task_params_struct {
      cuttable_wire_watcher *instance;
      StackType_t *stack_buffer;
      StaticTask_t task_buffer;
    } cuttable_wire_watcher_task_params;

    cuttable_wire_watcher_task_params m_task_params;

    enum class cuttable_wire_watcher_task_message {
      start,
      check_wires,
      stop
    };

    typedef struct cuttable_wire_watcher_task_queue_item_struct {
      cuttable_wire_watcher_task_message message;
      void *arg;
    } cuttable_wire_watcher_task_queue_item;

    void on_message( cuttable_wire_watcher_task_message msg );

    void start_sync();
    void stop_sync();

    static bool on_alarm( gptimer_handle_t timer,
                          const gptimer_alarm_event_data_t *edata,
                          void *user_ctx );
    
    void check_wires();
    
  public:

    enum class event {
      base = 0x3000,
      wire_recently_cut,
      wire_previously_cut
    };

    void set_event_loop_handle( esp_event_loop_handle_t esp_event_loop_handle );

    void add_event_listener( cuttable_wire_watcher::event event_id,
                             esp_event_handler_t event_handler );
    
    cuttable_wire_watcher();
    
    ::espena::cuttable_wire cutted_wire();

    static void task_loop( void *arg );

    void start();
    void stop();

    static const char* m_component_name;
    static const esp_event_base_t m_event_base;

  }; // class cuttable_wire_watcher

}; // namespace espena

#endif // __cuttable_wire_watcher_hpp__
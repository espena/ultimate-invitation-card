#ifndef __power_timeout_hpp__
#define __power_timeout_hpp__

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include "driver/gptimer.h"
#include <esp_event.h>
#include "event/event_dispatcher.hpp"

namespace espena::components {

  class power_timeout {

    static const int m_component_stack_size = 1024;

    const unsigned int m_timeout_minutes = 5;
    
    gptimer_handle_t m_timer;
    
    QueueHandle_t m_message_queue;

    ::espena::components::event::event_dispatcher m_event_dispatcher;

    typedef struct power_timeout_task_params_struct {
      power_timeout *instance;
      StackType_t *stack_buffer;
      StaticTask_t task_buffer;
    } power_timeout_task_params;

    power_timeout_task_params m_task_params;

    enum class power_timeout_task_message {
      reset_timer,
      on_alarm
    };

    typedef struct power_timeout_task_queue_item_struct {
      power_timeout_task_message message;
      void *arg;
    } power_timeout_task_queue_item;

    void on_message( power_timeout_task_message msg );

  public:

    enum class event {
      base = 0x2000,
      reset,
      timeout
    };

    void set_event_loop_handle( esp_event_loop_handle_t esp_event_loop_handle );

    void add_event_listener( power_timeout::event event_id,
                             esp_event_handler_t event_handler );
    
    power_timeout();
    
    static void task_loop( void *arg );

    static bool on_alarm( gptimer_handle_t timer,
                          const gptimer_alarm_event_data_t *edata,
                          void *user_ctx );
    
    void timeout();
    void reset();

    static const char* m_component_name;
    static const esp_event_base_t m_event_base;

  }; // class power_timeout

}; // namespace espena

#endif // __power_timeout_hpp__
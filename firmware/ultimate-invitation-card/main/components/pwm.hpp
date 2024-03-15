#ifndef __pwm_hpp__
#define __pwm_hpp__

#include <string>
#include <vector>
#include "driver/gpio.h"
#include "driver/gptimer.h"
#include "driver/ledc.h"
#include <freertos/queue.h>

namespace espena::components {

  class pwm {

    static std::vector<pwm *> m_instances;
    
    bool m_breathe = false;
    static bool m_breathe_out;

    static gptimer_handle_t m_pwm_timer;

    enum class pwm_task_message {
      on,
      off,
      breathe,
      stop_breathe,
      timed,
      beep,
      beeep,
      beeeep,
    };

    static const int m_component_stack_size = 768;

    typedef struct pwm_task_params_struct {
      pwm *instance;
      TaskHandle_t task_handle;
    } pwm_task_params;

    static pwm_task_params m_task_params;

    typedef struct pwm_task_queue_item_struct {
      pwm_task_message message;
      void *arg;
      int delay;
      int duration;
    } pwm_task_queue_item;

    static QueueHandle_t m_message_queue;

    static int m_pwm_count;

    gpio_num_t m_gpio_num;
    ledc_channel_t m_ledc_channel;

    static void task_loop( void *arg );

    static bool on_pwm_timer( gptimer_handle_t timer,
                              const gptimer_alarm_event_data_t *edata,
                              void *user_ctx );

    std::string m_group_name;

    void init_static_ledc();
    void init_static_pwm_timer();

    void init_pwm_channel();
    void init_pwm_task();

    void msg_queue_put( pwm_task_message msg );

    public:

      static const char* m_component_name;
      
      pwm( gpio_num_t gpio, std::string group_name );

      void breathe();
      void stop_breathe();

      static void breathe( std::string group_name );
      static void stop_breathe( std::string group_name );

      void on();
      void on( int brightness );

      void off();

      void timed( int delay, int duration );

      void beep();
      void beeep();
      void beeeep();

  }; // class pwm {

}; // namespace espena

#endif // __pwm_hpp__
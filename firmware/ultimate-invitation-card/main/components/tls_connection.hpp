#ifndef __tls_connection_hpp__
#define __tls_connection_hpp__

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include "esp_event.h"
#include "esp_tls.h"
#include "event/event_dispatcher.hpp"

namespace espena::components {

  class tls_connection {

    public:

      enum class event {
        base = 0x9000,
        init_failed,
        test_conn_failed
      };

    private:

      static const int m_component_stack_size = 8192*2;
      static const char *m_tls_connection_token;

      int m_post_status;
      bool m_tls_initialized;
      char *m_response_buffer;

      esp_tls_cfg_t m_cfg;
      esp_tls_t *m_tls;
      esp_tls_client_session_t *m_session;

      QueueHandle_t m_message_queue;

      typedef struct tls_connection_task_params_struct {
        tls_connection *instance;
        TaskHandle_t task_handle;
      } tls_connection_task_params;

      tls_connection_task_params m_task_params;

      enum class tls_connection_task_message {
        init,
        post
      };

      typedef struct tls_connection_task_queue_item_struct {
        tls_connection_task_message message;
        void *arg;
      } tls_connection_task_queue_item;

      static void task_loop( void *arg );
      void on_message( tls_connection_task_message msg, void *arg );

      static void event_handler( void *handler_arg,
                                esp_event_base_t event_base,
                                int32_t event_id,
                                void *event_params );

      void enqueue_simple_message( tls_connection_task_message msg );
      void connection_failure( const char *msg, tls_connection::event event_id );

      void init_sync();
      void post_sync( char *json );

      ::espena::components::event::event_dispatcher m_event_dispatcher;

      void heap_report();

    public:

      static const char* m_component_name;
      static const esp_event_base_t m_event_base;

      tls_connection();
      ~tls_connection();

      void set_event_loop_handle( esp_event_loop_handle_t esp_event_loop_handle );

      void init();
      bool init_await();

      void post( std::string json );
      bool post_await( std::string json );

  }; // class tls_connection

}; // namespace espena

#endif // __tls_connection_hpp__
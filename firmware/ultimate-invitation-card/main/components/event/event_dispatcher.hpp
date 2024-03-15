#ifndef __event_dispatcher_app__
#define __event_dispatcher_app__

#include <esp_event.h>
#include "i_event_dispatcher.hpp"

namespace espena::components::event {

  class event_dispatcher : public i_event_dispatcher {

    esp_err_t m_handle_registered;
    esp_event_loop_handle_t m_event_loop_handle;

    public:

      event_dispatcher();

      ~event_dispatcher();

      void set_event_loop_handle( esp_event_loop_handle_t );

      void add_event_listener( esp_event_base_t, int32_t, esp_event_handler_t );

      void add_event_listener( esp_event_base_t, int32_t, esp_event_handler_t, void * instance );

      void dispatch( esp_event_base_t, int32_t, void *, size_t );

      void dispatch( esp_event_base_t event_base, int32_t event_id );

      void remove_event_listener( esp_event_base_t event_base,
                                  int32_t event_id,
                                  esp_event_handler_t event_handler );

      void remove_event_listener( int32_t event_id,
                                  esp_event_handler_t event_handler );

      void remove_event_listener( esp_event_base_t event_base,
                                  esp_event_handler_t event_handler );

      void remove_event_listener( esp_event_handler_t event_handler );

  }; // class event_dispatcher

}; // namespace espena::components::event

#endif // __event_dispatcher_app__

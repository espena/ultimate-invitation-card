#ifndef __captive_portal_hpp__
#define __captive_portal_hpp__

#include "captive_portal_wifi.hpp"
#include "captive_portal_dns.hpp"
#include "captive_portal_http.hpp"

namespace espena::components {

  class captive_portal {

    static const int m_component_stack_size = 3072;

    captive_portal_wifi m_wifi;
    captive_portal_dns m_dns;
    captive_portal_http m_http;

    esp_event_loop_handle_t m_event_loop_handle;

    std::string m_json_network_list;

    static void event_handler( void *handler_arg,
                               esp_event_base_t event_base,
                               int32_t event_id,
                               void *event_params );

    void on_http_ssid_select( captive_portal_wifi::credentials *creds );
    void on_wifi_network_ready();
    void on_got_ip();
    void on_network_scan_complete( char *json );

    public:

      static const char *m_component_name;
      static const char *m_ssid;

      captive_portal();

      void add_event_listener( captive_portal_wifi::event event_id,
                               esp_event_handler_t event_handler,
                               void *instance );

      void start();
      void stop();

      void wifi_connect(); // < Try to connect with stored credentials

      bool is_provisioning() {
        return m_wifi.is_provisioning();
      };

  }; // class captive_portal

}; // namespace espena::components

#endif // __captive_portal_hpp__
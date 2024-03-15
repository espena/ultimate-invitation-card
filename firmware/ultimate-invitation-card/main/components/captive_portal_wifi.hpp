#ifndef __captive_portal_wifi_hpp__
#define __captive_portal_wifi_hpp__

#include <string>
#include <vector>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <freertos/event_groups.h>
#include "esp_event.h"
#include "esp_wifi.h"
#include "captive_portal_wifi.hpp"
#include "event/i_event_dispatcher.hpp"
#include "event/event_dispatcher.hpp"

namespace espena::components {

  class captive_portal_wifi : public event::i_event_dispatcher {

    public:

        typedef struct credentials {
          char ssid[ 33 ];
          char password[ 64 ];
        } credentials;

    private:

      std::string m_ap_ssid;
      esp_netif_t *m_netif_ap;
      esp_netif_t *m_netif_sta;

      bool m_is_provisioning;

      credentials m_sta_creds;

      esp_netif_ip_info_t m_ap_ip_info;

      wifi_config_t m_cfg;

      std::vector<std::string> m_networks;

      QueueHandle_t m_message_queue;
      EventGroupHandle_t m_event_group;

      event::event_dispatcher m_external_event_dispatcher;
      event::event_dispatcher m_internal_event_dispatcher;

      typedef struct captive_portal_wifi_task_params_struct {
        captive_portal_wifi *instance;
        TaskHandle_t task_handle;
      } captive_portal_wifi_task_params;

      captive_portal_wifi_task_params m_task_params;

      enum class captive_portal_wifi_task_message {
        init,
        scan,
        connect,
        start,
        stop
      };

      typedef struct captive_portal_wifi_task_queue_item_struct {
        captive_portal_wifi_task_message message;
        void *arg;
      } captive_portal_wifi_task_queue_item;

      static void task_loop( void *arg );
      void on_message( captive_portal_wifi_task_message msg, void *arg );

      static void event_handler( void *handler_arg,
                                esp_event_base_t event_base,
                                int32_t event_id,
                                void *event_params );

      void on_sta_connected();
      void on_sta_login_failure();
      void on_sta_ap_not_found();
      void on_sta_connection_failure();
      void on_sta_disconnected( wifi_event_sta_disconnected_t *disconnected );
      void on_sta_got_ip();

      void dispatch_network_list();
      void network_scan();

      void init_nvs();
      void init_netif();
      void init_wifi();
      void init_wifi_ap();
      void init_wifi_sta();
      void init_events();

      void init_sync();
      void scan_sync();
      void start_sync();
      void connect_sync( credentials *creds );
      void stop_sync();

      void enqueue_simple_message( captive_portal_wifi_task_message msg );

    public:

      static const esp_event_base_t m_event_base;

      enum class event {
        base = 0x3000,
        network_connecting,
        network_ready,
        client_connected,
        provisioning_aborted,
        provisioning_required,
        sta_disconnected,
        login_failure,
        ap_not_found,
        got_ip,
        network_scan_complete
      };

      static const char *m_component_name;
      static const size_t m_component_stack_size = 8196;

      captive_portal_wifi( const char *ssid );

      void set_event_loop_handle( esp_event_loop_handle_t esp_event_loop_handle );
      void add_event_listener( int32_t event_id,
                               esp_event_handler_t event_handler,
                               void *instance );

      bool is_provisioning() {
        return m_is_provisioning;
      };

      // Begin async methods
      void init();
      void scan();
      void connect( credentials *creds );
      void connect();
      void start();
      void stop();

      // End async methods

  }; // class captive_portal_wifi

}; // namespace espena::components

#endif // __captive_portal_wifi_hpp__
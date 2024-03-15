#include "captive_portal.hpp"
#include "captive_portal_wifi.hpp"
#include "captive_portal_dns.hpp"
#include "captive_portal_http.hpp"
#include "esp_log.h"
#include "esp_wifi.h"
#include "../p13n.hpp"

using namespace espena::components;

const char *captive_portal::m_component_name = "captive_portal";
const char *captive_portal::m_ssid = P13N_SSID;

captive_portal::captive_portal() : m_wifi( m_ssid ),
                                   m_event_loop_handle( nullptr ),
                                   m_json_network_list( "[]" )
{
  esp_event_loop_args_t loop_args = {
    .queue_size = 1000,
    .task_name = "captive_portal_event_loop",
    .task_priority = uxTaskPriorityGet( NULL ),
    .task_stack_size = m_component_stack_size,
    .task_core_id = tskNO_AFFINITY
  };
  esp_event_loop_create( &loop_args, &m_event_loop_handle );
  m_http.set_event_loop_handle( m_event_loop_handle );
  m_http.add_event_listener( static_cast<int32_t>( captive_portal_http::event::ssid_select ),
                             &captive_portal::event_handler,
                             this );
  m_wifi.set_event_loop_handle( m_event_loop_handle );
  m_wifi.add_event_listener( ESP_EVENT_ANY_ID,
                             &captive_portal::event_handler,
                             this );
  m_wifi.init();

}

void captive_portal::add_event_listener( captive_portal_wifi::event event_id,
                                         esp_event_handler_t event_handler,
                                         void *instance )
{
  m_wifi.add_event_listener( static_cast<int32_t>( event_id ),
                             event_handler,
                             instance );
}

void captive_portal::event_handler( void *handler_arg,
                                    esp_event_base_t event_base,
                                    int32_t event_id,
                                    void *event_params )
{
  captive_portal *inst = static_cast<captive_portal *>( handler_arg );
  if( event_base == captive_portal_http::m_event_base ) {
    switch( static_cast<captive_portal_http::event>( event_id ) ) {
      case captive_portal_http::event::ssid_select:
        {
          inst->on_http_ssid_select( static_cast<captive_portal_wifi::credentials *>( event_params ) );
        }
        break;
      default:
        break;
    }
  }
  else if( event_base == captive_portal_wifi::m_event_base ) {
    switch( static_cast<captive_portal_wifi::event>( event_id ) ) {
      case captive_portal_wifi::event::network_ready:
        inst->on_wifi_network_ready();
        break;
      case captive_portal_wifi::event::network_scan_complete:
        inst->on_network_scan_complete( static_cast<char *>( event_params ) );
        break;
      case captive_portal_wifi::event::got_ip:
        inst->on_got_ip();
        break;
      default:
        break; 
    }
  }
}

void captive_portal::on_http_ssid_select( captive_portal_wifi::credentials *creds ) {
  ESP_LOGI( m_component_name, "SSID selected: %s", creds->ssid );
  m_dns.stop();
  m_http.stop();
  m_wifi.connect( creds );
}

void captive_portal::on_wifi_network_ready() {

  ESP_LOGI( m_component_name, "Network ready" );

  m_dns.init();
  m_dns.start();
  m_http.init();
  m_http.start();
}

void captive_portal::on_network_scan_complete( char *json ) {
  m_http.set_network_list( json );
}

void captive_portal::on_got_ip() {
  ESP_LOGI( m_component_name, "Got IP address" );
}

void captive_portal::start() {
  ESP_LOGI( m_component_name, "Starting captive portal at SSID %s", m_ssid );
  m_wifi.start();
  m_wifi.scan();
}

void captive_portal::stop() {
  m_wifi.stop();
  m_dns.stop();
  m_http.stop();
}

void captive_portal::wifi_connect() {
  m_wifi.connect();
}

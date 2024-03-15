#include <memory.h>
#include <algorithm>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <freertos/event_groups.h>
#include "lwip/ip4_addr.h"
#include "lwip/dns.h"
#include "esp_log.h"
#include "esp_event.h"
#include "esp_wifi.h"
#include "nvs_flash.h"
#include "../application.hpp"
#include "captive_portal_wifi.hpp"
#include "../p13n.hpp"

using namespace espena::components;

const char *captive_portal_wifi::m_component_name = "captive_portal_wifi";
const esp_event_base_t captive_portal_wifi::m_event_base = "CAPTIVE_PORTAL_WIFI_EVENT";

captive_portal_wifi::captive_portal_wifi( const char *ssid ) : m_ap_ssid( ssid ),
                                                               m_netif_ap( nullptr ),
                                                               m_netif_sta( nullptr ),
                                                               m_is_provisioning( true )
{
  memset( &m_sta_creds, 0x00, sizeof( credentials ) );
  memset( &m_cfg, 0x00, sizeof( wifi_config_t ) );

  memset( &m_ap_ip_info, 0x00, sizeof( esp_netif_ip_info_t ) );
  IP4_ADDR( &m_ap_ip_info.ip, 25, 6, 19, 74 ); // Default IP before DHCP provisioning
  IP4_ADDR( &m_ap_ip_info.gw, 25, 6, 19, 74 );
  IP4_ADDR( &m_ap_ip_info.netmask, 255, 0, 0, 0 );

  m_message_queue = xQueueCreate( 50, sizeof( captive_portal_wifi_task_queue_item ) );
  m_event_group = xEventGroupCreate();
  m_task_params.instance = this;
  esp_event_loop_create_default();

  xTaskCreate( &captive_portal_wifi::task_loop,
               m_component_name,
               m_component_stack_size,
               &m_task_params,
               2 | portPRIVILEGE_BIT,
               &m_task_params.task_handle );
}

void captive_portal_wifi::set_event_loop_handle( esp_event_loop_handle_t esp_event_loop_handle )
{
  m_external_event_dispatcher.set_event_loop_handle( esp_event_loop_handle );
}

void captive_portal_wifi::add_event_listener( int32_t event_id,
                                              esp_event_handler_t event_handler,
                                              void *instance )
{
  m_external_event_dispatcher.add_event_listener( m_event_base,
                                                  event_id,
                                                  event_handler,
                                                  instance );
}

void captive_portal_wifi::task_loop( void *arg )
{
  captive_portal_wifi_task_params *params = static_cast<captive_portal_wifi_task_params *>( arg );
  captive_portal_wifi *inst = params->instance;
  captive_portal_wifi_task_queue_item item;
  memset( &item, 0x00, sizeof( captive_portal_wifi_task_queue_item ) );
  while( 1 ) {
    if( xQueueReceive( inst->m_message_queue, &item, 10 ) ) {
      inst->on_message( item.message, item.arg );
    }
  }
}

void captive_portal_wifi::on_message( captive_portal_wifi_task_message msg, void *arg )
{
  switch( msg ) {
    case captive_portal_wifi_task_message::init:
      init_sync();
      break;
    case captive_portal_wifi_task_message::scan:
      scan_sync();
      break;
    case captive_portal_wifi_task_message::connect:
      connect_sync( static_cast<credentials *>( arg ) );
      break;
    case captive_portal_wifi_task_message::start:
      start_sync();
      break;
    case captive_portal_wifi_task_message::stop:
      stop_sync();
      break;
  }
}

void captive_portal_wifi::event_handler( void *handler_arg,
                                         esp_event_base_t event_base,
                                         int32_t event_id,
                                         void *event_params )
{
  captive_portal_wifi *inst = static_cast<captive_portal_wifi *>( handler_arg );
  wifi_event_sta_disconnected_t *disconnected = nullptr;
  ESP_LOGI( "WIFI_EVENT_HANDLER", "Got event %li at %s", event_id, event_base );
  switch( event_id ) {
    case WIFI_EVENT_AP_START:
      inst->m_external_event_dispatcher.dispatch( m_event_base, static_cast<int32_t>( event::network_ready ) );
      break;
    case WIFI_EVENT_AP_STACONNECTED:
      inst->m_external_event_dispatcher.dispatch( m_event_base, static_cast<int32_t>( event::client_connected ) );
      break;
    case WIFI_EVENT_AP_STOP:

      break;
    case WIFI_EVENT_AP_STADISCONNECTED:
      disconnected = static_cast<wifi_event_sta_disconnected_t *>( event_params );
      inst->on_sta_disconnected( disconnected );
      if( inst->m_is_provisioning ) {
        inst->m_external_event_dispatcher.dispatch( m_event_base, static_cast<int32_t>( event::provisioning_aborted ) );
        inst->m_is_provisioning = false;
      }
      break;
    case WIFI_EVENT_STA_CONNECTED:
      inst->on_sta_connected();
      break;
    case WIFI_EVENT_STA_DISCONNECTED:
      {
        disconnected = static_cast<wifi_event_sta_disconnected_t *>( event_params );
        ESP_LOGI( "WIFI_EVENT_HANDLER", "STA disconnected with reason %i", disconnected->reason );
        inst->m_external_event_dispatcher.dispatch( m_event_base, static_cast<int32_t>( event::sta_disconnected ) );
        switch( disconnected->reason ) {
          case WIFI_REASON_AUTH_EXPIRE:
          case WIFI_REASON_4WAY_HANDSHAKE_TIMEOUT:
          case WIFI_REASON_BEACON_TIMEOUT:
          case WIFI_REASON_ASSOC_FAIL:
          case WIFI_REASON_HANDSHAKE_TIMEOUT:
          case WIFI_REASON_AUTH_FAIL:
            inst->on_sta_login_failure();
            break;
          case WIFI_REASON_NO_AP_FOUND:
            inst->on_sta_ap_not_found();
            break;
          case WIFI_REASON_ASSOC_LEAVE:
            ESP_LOGI( "WIFI_EVENT_HANDLER", "STA disconnected due to association leave" );
            break;
        }
      }
      break;
    case IP_EVENT_STA_GOT_IP:
      inst->m_external_event_dispatcher.dispatch( m_event_base, static_cast<int32_t>( event::got_ip ) );
      inst->on_sta_got_ip();
      break;
  }
}

void captive_portal_wifi::on_sta_connected()
{
  ESP_LOGI( m_component_name, "STA connected" );
}

void captive_portal_wifi::on_sta_login_failure()
{
  ESP_LOGI( m_component_name, "STA login failure" );
  m_external_event_dispatcher.dispatch( m_event_base, static_cast<int32_t>( event::login_failure ) );
}

void captive_portal_wifi::on_sta_ap_not_found()
{
  ESP_LOGI( m_component_name, "AP not found" );
  m_external_event_dispatcher.dispatch( m_event_base, static_cast<int32_t>( event::ap_not_found ) );
}

void captive_portal_wifi::on_sta_connection_failure()
{
  ESP_LOGI( m_component_name, "STA connection failure" );
}

void captive_portal_wifi::on_sta_disconnected( wifi_event_sta_disconnected_t *disconnected )
{
  ESP_LOGI( m_component_name, "STA disconnected" );
}

void captive_portal_wifi::on_sta_got_ip()
{
  esp_netif_get_ip_info( m_netif_sta, &m_ap_ip_info );
  const esp_ip4_addr_t *ip = &m_ap_ip_info.ip;
  init_wifi_ap();
  char ip_str[ 16 ];
  esp_ip4addr_ntoa( ip, ip_str, sizeof( ip_str ) );
  ESP_LOGI( m_component_name, "STA got IP: %s", ip_str );
}

void captive_portal_wifi::dispatch_network_list()
{
  std::string json  = "[";
  for( std::vector<std::string>::iterator i = m_networks.begin(); i != m_networks.end(); i++ ) {
    json += "\"";
    json += *i;
    json += "\"";
    if( i != m_networks.end() - 1 ) {
      json += ",";
    }
  }
  json += "]";
  const size_t json_len = json.length() + 1;
  char *json_buf = new char[ json_len ];
  memcpy( json_buf, json.c_str(), json_len );
  m_external_event_dispatcher.dispatch( m_event_base,
                                        static_cast<int32_t>( event::network_scan_complete ),
                                        json_buf,
                                        json_len );
  delete [] json_buf;
}

void captive_portal_wifi::init_nvs()
{
  esp_err_t err = nvs_flash_init();
  if( err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND ) {
    ESP_ERROR_CHECK( nvs_flash_erase() );
    err = nvs_flash_init();
  }
  ESP_ERROR_CHECK( err );
}

void captive_portal_wifi::init_netif()
{

}

void captive_portal_wifi::init_wifi()
{
  wifi_init_config_t cfg_init = WIFI_INIT_CONFIG_DEFAULT();
  nvs_flash_init();
  cfg_init.nvs_enable = true;
  esp_wifi_init( &cfg_init );
  esp_wifi_set_storage( WIFI_STORAGE_FLASH );
  esp_wifi_set_mode( WIFI_MODE_APSTA );
}

void captive_portal_wifi::init_wifi_ap()
{
  wifi_mode_t mode;
  ESP_ERROR_CHECK( esp_wifi_get_mode( &mode ) );
  if( mode != WIFI_MODE_APSTA && mode != WIFI_MODE_AP ) {
    return;
  }

  ESP_ERROR_CHECK( esp_netif_init() );

  if( m_netif_ap ) {
    esp_netif_destroy( m_netif_ap );
    m_netif_ap = nullptr;
  }
  m_netif_ap = esp_netif_create_default_wifi_ap();
  assert( m_netif_ap );

  esp_netif_dhcps_stop( m_netif_ap );
  esp_netif_set_ip_info( m_netif_ap, &m_ap_ip_info );
  esp_netif_dhcps_start( m_netif_ap );

  ESP_LOGI( m_component_name, "Network interface for AP initialized" );

  memcpy( reinterpret_cast<char *>( m_cfg.ap.ssid ), m_ap_ssid.c_str(), m_ap_ssid.length() );

  m_cfg.ap.ssid_len = m_ap_ssid.length();
  m_cfg.ap.channel = 7;
  m_cfg.ap.password[ 0 ] = '\0';
  m_cfg.ap.max_connection = 10;
  m_cfg.ap.authmode = WIFI_AUTH_OPEN;

  ESP_ERROR_CHECK( esp_wifi_set_config( WIFI_IF_AP, &m_cfg ) );

}

void captive_portal_wifi::init_wifi_sta()
{

  wifi_mode_t mode;
  ESP_ERROR_CHECK( esp_wifi_get_mode( &mode ) );
  if( mode != WIFI_MODE_APSTA && mode != WIFI_MODE_STA ) {
    return;
  }

  if( m_netif_sta ) {
    esp_netif_destroy( m_netif_sta );
    m_netif_sta = nullptr;
  }
  m_netif_sta = esp_netif_create_default_wifi_sta();
  assert( m_netif_sta );

  ESP_LOGI( m_component_name, "Network interfce for STA initialized" );

  wifi_init_config_t cfg_init = WIFI_INIT_CONFIG_DEFAULT();
  ESP_ERROR_CHECK( esp_wifi_init( &cfg_init ) );
  
  memcpy( reinterpret_cast<char *>( m_cfg.sta.ssid ),
          m_sta_creds.ssid,
          sizeof( credentials::ssid ) );

  memcpy( reinterpret_cast<char *>( m_cfg.sta.password ),
          m_sta_creds.password,
          sizeof( credentials::password ) );

  m_cfg.sta.scan_method = WIFI_ALL_CHANNEL_SCAN;
  m_cfg.sta.failure_retry_cnt = 5;
  m_cfg.sta.threshold.authmode = WIFI_AUTH_WPA_PSK;
  m_cfg.sta.sae_pwe_h2e = WPA3_SAE_PWE_BOTH;

  ESP_ERROR_CHECK( esp_wifi_set_config( WIFI_IF_STA, &m_cfg ) );
}

void captive_portal_wifi::network_scan()
{
  wifi_scan_config_t cfg_scan;
  memset( &cfg_scan, 0x00, sizeof( wifi_scan_config_t ) );
  cfg_scan.show_hidden = false; 
  esp_wifi_scan_start( &cfg_scan, true );
  wifi_ap_record_t ap_records[ 10 ];
  uint16_t ap_count = sizeof( ap_records ) / sizeof( wifi_ap_record_t );
  memset( ap_records, 0x00, sizeof( ap_records ) );
  esp_wifi_scan_get_ap_records( &ap_count, ap_records );
  m_networks.clear();
  for( int i = 0; i < ap_count; i++ ) {
    m_networks.push_back( reinterpret_cast<char *>( ap_records[ i ].ssid ) );
    ESP_LOGI( m_component_name, 
              "AP %d: %32s: %d",
              i,
              ( char * ) ap_records[ i ].ssid,
              ap_records[ i ].rssi );
  }
  dispatch_network_list();
}

void captive_portal_wifi::init_events()
{
  m_internal_event_dispatcher.add_event_listener( WIFI_EVENT,
                                         ESP_EVENT_ANY_ID,
                                         &captive_portal_wifi::event_handler,
                                         this );
  m_internal_event_dispatcher.add_event_listener( IP_EVENT,
                                         ESP_EVENT_ANY_ID,
                                         &captive_portal_wifi::event_handler,
                                         this );
}

void captive_portal_wifi::init_sync()
{
  init_nvs();
  init_netif();
  init_wifi();
  init_wifi_ap();
  init_events();
}

void captive_portal_wifi::scan_sync()
{
  ESP_LOGI( m_component_name, "Scanning for WiFi access points" );
  network_scan();
}

void captive_portal_wifi::start_sync()
{
  ESP_LOGI( m_component_name, "Starting WiFi AP" );
  esp_wifi_start();
}

void captive_portal_wifi::connect_sync( credentials *creds )
{
  m_is_provisioning = false;
  esp_wifi_stop();
  if( creds ) {
    m_external_event_dispatcher.dispatch( m_event_base,
                                          static_cast<int32_t>( event::network_connecting ),
                                          creds->ssid,
                                          sizeof( credentials::ssid ) );

    ESP_LOGI( m_component_name, "Connecting to %s...", creds->ssid );

    memcpy( reinterpret_cast<char *>( &m_cfg.sta.ssid ), creds->ssid, std::min( sizeof( credentials::ssid ), 31u ) );
    memcpy( reinterpret_cast<char *>( &m_cfg.sta.password ), creds->password, std::min( sizeof( credentials::password ), 63u ) );
    memcpy( &m_sta_creds, creds, sizeof( credentials ) );
    delete creds;
  }
  else {
    ESP_LOGI( m_component_name, "Using stored credentials (if exists)" );
    esp_wifi_get_config( WIFI_IF_STA, &m_cfg );
    ESP_LOGI( m_component_name, "Stored SSID: %s", m_cfg.sta.ssid );
  }

  wifi_init_config_t cfg_init = WIFI_INIT_CONFIG_DEFAULT();
  cfg_init.nvs_enable = true;

  ESP_ERROR_CHECK( esp_wifi_init( &cfg_init ) );
  ESP_ERROR_CHECK( esp_wifi_set_storage( WIFI_STORAGE_FLASH ) );
  ESP_ERROR_CHECK( esp_wifi_set_mode( WIFI_MODE_STA ) );

  if( m_netif_sta ) {
    esp_netif_destroy( m_netif_sta );
    m_netif_sta = nullptr;
  }
  m_netif_sta = esp_netif_create_default_wifi_sta();
  assert( m_netif_sta );

  ESP_LOGI( m_component_name, "Network interfce for STA initialized" );
  
  m_cfg.sta.scan_method = WIFI_ALL_CHANNEL_SCAN;
  m_cfg.sta.failure_retry_cnt = 5;
  m_cfg.sta.threshold.authmode = WIFI_AUTH_WPA_PSK;
  m_cfg.sta.sae_pwe_h2e = WPA3_SAE_PWE_BOTH;

  ESP_ERROR_CHECK( esp_wifi_set_config( WIFI_IF_STA, &m_cfg ) );
  ESP_ERROR_CHECK( esp_wifi_start() );

  esp_err_t res = esp_wifi_connect();
  if( res != ESP_OK ) {
    ESP_LOGI( m_component_name, "Failed to connect to WiFi network, run provisioning" );
    m_external_event_dispatcher.dispatch( m_event_base, static_cast<int32_t>( event::provisioning_required ) );
  }
  else {
    ESP_LOGI( m_component_name, "Connected to WiFi network" );
  }
}

void captive_portal_wifi::stop_sync()
{
  ESP_LOGI( m_component_name, "Stopping WiFi AP" );
  esp_wifi_stop();
  init();
}

void captive_portal_wifi::enqueue_simple_message( captive_portal_wifi_task_message msg )
{
  captive_portal_wifi_task_queue_item item = { msg, nullptr };
  xQueueSend( m_message_queue, &item, 10 );
}

// Asynchronous methods (called from other tasks)

void captive_portal_wifi::init()
{
  enqueue_simple_message( captive_portal_wifi_task_message::init );
}

void captive_portal_wifi::start()
{
  enqueue_simple_message( captive_portal_wifi_task_message::start );
}

void captive_portal_wifi::scan()
{
  enqueue_simple_message( captive_portal_wifi_task_message::scan );
}

void captive_portal_wifi::connect( credentials *creds )
{
  captive_portal_wifi_task_queue_item item;
  item.message = captive_portal_wifi_task_message::connect;
  item.arg = new credentials;
  memcpy( item.arg, creds, sizeof( credentials ) );
  xQueueSend( m_message_queue, &item, 10 );
}

void captive_portal_wifi::connect()
{
  enqueue_simple_message( captive_portal_wifi_task_message::connect );
}

void captive_portal_wifi::stop()
{
  enqueue_simple_message( captive_portal_wifi_task_message::stop );
}

#include <memory.h>
#include <string>
#include <string.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>

#include "esp_log.h"
#include "esp_http_server.h"

#include "captive_portal_http.hpp"

#include "../resources/html_captive_portal.hpp"
#include "captive_portal_wifi.hpp"

using namespace espena::components;

const char *captive_portal_http::m_component_name = "captive_portal_http";
const esp_event_base_t captive_portal_http::m_event_base = "CAPTIVE_PORTAL_HTTP_EVENT";

captive_portal_http::captive_portal_http() : m_message_queue( nullptr ),
                                             m_server( nullptr )
{
  m_cfg.uri_match_fn = httpd_uri_match_wildcard;
  m_cfg.lru_purge_enable = true;
  m_message_queue = xQueueCreate( 50, sizeof( captive_portal_http_task_queue_item ) );
  m_task_params.instance = this;

  m_task_params.stack_buffer = ( StackType_t * ) heap_caps_malloc( m_component_stack_size,
                                                                   MALLOC_CAP_SPIRAM );

  xTaskCreateStatic( &captive_portal_http::task_loop,
                     m_component_name,
                     m_component_stack_size,
                     &m_task_params,
                     4 | portPRIVILEGE_BIT,
                     m_task_params.stack_buffer,
                     &m_task_params.task_buffer ); 

}

void captive_portal_http::set_event_loop_handle( esp_event_loop_handle_t esp_event_loop_handle ) {
  m_event_dispatcher.set_event_loop_handle( esp_event_loop_handle );
}

void captive_portal_http::add_event_listener( int32_t event_id,
                                              esp_event_handler_t event_handler,
                                              void *instance )
{
  m_event_dispatcher.add_event_listener( m_event_base,
                                         event_id,
                                         event_handler,
                                         instance );
}

void captive_portal_http::enqueue_simple_message( captive_portal_http_task_message msg ) {
  captive_portal_http_task_queue_item item = { msg, nullptr };
  xQueueSend( m_message_queue, &item, 10 );
}

void captive_portal_http::task_loop( void *arg ) {
  captive_portal_http_task_params *params = static_cast<captive_portal_http_task_params *>( arg );
  captive_portal_http *inst = params->instance;
  captive_portal_http_task_queue_item item;
  memset( &item, 0x00, sizeof( captive_portal_http_task_queue_item ) );
  while( 1 ) {
    if( xQueueReceive( inst->m_message_queue, &item, 10 ) ) {
      inst->on_message( item.message, item.arg );
    }
  }
}

esp_err_t captive_portal_http::request_handler( httpd_req_t *req ) {
  captive_portal_http *inst = static_cast<captive_portal_http *>( req->user_ctx );
  return inst->on_request( req );
}

esp_err_t captive_portal_http::on_request( httpd_req_t *req ) {

  const size_t req_hdr_host_len = httpd_req_get_hdr_value_len( req, "Host" );
  std::string hostname;
  hostname.resize( req_hdr_host_len + 1 );

  httpd_req_get_hdr_value_str( req, "Host", &hostname[ 0 ], req_hdr_host_len + 1 );

  ESP_LOGI( m_component_name, "Request for %s", req->uri );

  std::string uri( req->uri );
  if( uri == "/ssid_list" ) {

    const char *json_buf = m_json_network_list.c_str();
    const size_t json_len = m_json_network_list.length();

    httpd_resp_set_status( req, "302 Found" ); 
    httpd_resp_set_type( req, "application/json; charset=utf-8;" );
    httpd_resp_send( req, json_buf, json_len );

  }
  else if( uri == "/ssid_auth" ) {

    char *buf = new char[ req->content_len + 1 ];
    size_t offset = 0;
    int retval = 0;

    while( offset < req->content_len ) {
      retval = httpd_req_recv( req, buf + offset, req->content_len - offset );
      if( retval <= 0 ) {
        break;
      }
      offset += retval;
    }

    buf[ offset ] = '\0';

    captive_portal_wifi::credentials creds;
    memset( &creds, 0x00, sizeof( captive_portal_wifi::credentials ) );

    char *ssid = strstr( buf, "\"ssid\":\"" ) + 8;
    char *password = strstr( buf, "\"password\":\"" ) + 12;

    if( ssid && strstr( ssid, "\"," ) ) {
      *( strstr( ssid, "\"," ) ) = '\0';
    }
    else {
      ssid = nullptr;
    }

    if( password && strstr( password, "\"}" ) ) {
      *( strstr( password, "\"}" ) ) = '\0';
    }
    else {
      password = nullptr;
    }

    if( ssid && password ) {
      ESP_LOGI( m_component_name, "Received SSID %s with password", ssid );
      strncpy( creds.ssid, ssid, sizeof( creds.ssid ) );
      strncpy( creds.password, password, sizeof( creds.password ) );
      m_event_dispatcher.dispatch( m_event_base,
                                   static_cast<int32_t>( event::ssid_select ),
                                   &creds,
                                   sizeof( captive_portal_wifi::credentials ) );
    }
    else {
      ESP_LOGI( m_component_name, "Received invalid SSID and/or password" );
    }

    delete [] buf;
    buf = nullptr;

    const char *json_buf = "{\"status\":\"ok\"}";
    const size_t json_len = strlen( json_buf );
    
    httpd_resp_set_status( req, "302 Found" ); 
    httpd_resp_set_type( req, "application/json; charset=utf-8;" );
    httpd_resp_send( req, json_buf, json_len );

  }
  else {

    httpd_resp_set_status( req, "302 Found" ); 
    httpd_resp_set_type( req, "text/html; charset=utf-8;" );

    ESP_LOGI( m_component_name, "Respond with captive portal" );
    httpd_resp_send( req, html::captive_portal, sizeof( html::captive_portal ) );

  }
  return ESP_OK;
}

void captive_portal_http::on_message( captive_portal_http_task_message msg, void *arg ) {
  captive_portal_http_task_queue_item *item = nullptr;
  switch( msg ) {
    case captive_portal_http_task_message::set_network_list:
      m_json_network_list = static_cast<char *>( arg );
      free( arg );
      break;
    case captive_portal_http_task_message::init:
      init_sync();
      break;
    case captive_portal_http_task_message::start:
      start_sync();
      break;
    case captive_portal_http_task_message::stop:
      stop_sync();
      break;
  }
}

void captive_portal_http::init_sync() {

}

void captive_portal_http::start_sync() {
  stop_sync(); // Assert server is not running

  if( httpd_start( &m_server, &m_cfg ) != ESP_OK ) {
    ESP_LOGE( m_component_name, "Failed to start HTTP server" );
    return;
  }

  httpd_uri_t location;

  location.uri = "/ssid_auth",
  location.method = HTTP_POST,
  location.handler = request_handler,
  location.user_ctx = this;

  httpd_register_uri_handler( m_server, &location );

  location.uri = "/*",
  location.method = HTTP_GET,
  location.handler = request_handler,
  location.user_ctx = this;

  httpd_register_uri_handler( m_server, &location );

  ESP_LOGI( m_component_name, "HTTP server running" );
  
}

void captive_portal_http::stop_sync() {
  if( m_server ) {
    httpd_stop( m_server );
    m_server = nullptr;
    ESP_LOGI( m_component_name, "HTTP server stopped" );
  }
}

void captive_portal_http::set_network_list( char *json ) {
  captive_portal_http_task_queue_item item;
  item.message = captive_portal_http_task_message::set_network_list;
  item.arg = strdup( json );
  xQueueSend( m_message_queue, &item, 10 );  
}

void captive_portal_http::init() {
  enqueue_simple_message( captive_portal_http_task_message::init );
}

void captive_portal_http::start() {
  enqueue_simple_message( captive_portal_http_task_message::start );
}

void captive_portal_http::stop() {
  enqueue_simple_message( captive_portal_http_task_message::stop );
}

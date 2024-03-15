#include <memory.h>
#include <string>
#include <vector>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include "lwip/ip_addr.h"
#include "lwip/dns.h"
#include "esp_event.h"
#include "esp_tls.h"
#include "esp_log.h"
#include "tls_connection.hpp"

using namespace espena::components;

extern const uint8_t isrgroot_pem_start[] asm( "_binary_isrgrootx1_pem_start" );
extern const uint8_t isrgroot_pem_end[] asm( "_binary_isrgrootx1_pem_end" );

const char *tls_connection::m_component_name = "tls_connection";
                                                      
const char *tls_connection::m_tls_connection_token = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"; // << Replace with your token
const esp_event_base_t tls_connection::m_event_base = "TLS_CONNECTION_EVENT";

tls_connection::tls_connection() : m_post_status( 0 ),
                                   m_tls_initialized( false ),
                                   m_response_buffer( nullptr ),
                                   m_tls( nullptr ),
                                   m_session( nullptr ),
                                   m_message_queue( nullptr )
{
  memset( &m_cfg, 0x00, sizeof( m_cfg ) );
  m_message_queue = xQueueCreate( 50, sizeof( tls_connection_task_queue_item ) );
  esp_event_loop_create_default();
  m_task_params.instance = this;
  xTaskCreate( &tls_connection::task_loop,
               m_component_name,
               m_component_stack_size,
               &m_task_params,
               1,
               &m_task_params.task_handle );
}

tls_connection::~tls_connection()
{
  if( m_response_buffer ) {
    delete [] m_response_buffer;
  }
  if( m_session ) {
    esp_tls_free_client_session( m_session );
  }
  if( m_message_queue ) {
    vQueueDelete( m_message_queue );
  }
}

void tls_connection::set_event_loop_handle( esp_event_loop_handle_t esp_event_loop_handle )
{
  m_event_dispatcher.set_event_loop_handle( esp_event_loop_handle );
}

void tls_connection::task_loop( void *arg )
{
  tls_connection_task_params *params = static_cast<tls_connection_task_params *>( arg );
  tls_connection *inst = params->instance;
  tls_connection_task_queue_item item;
  memset( &item, 0x00, sizeof( tls_connection_task_queue_item ) );
  while( 1 ) {
    if( xQueueReceive( inst->m_message_queue, &item, 10 ) ) {
      inst->on_message( item.message, item.arg );
    }
  }
}

void tls_connection::on_message( tls_connection_task_message msg, void *arg )
{
  switch( msg) {
    case tls_connection_task_message::init:
      init_sync();
      break;
    case tls_connection_task_message::post:
      post_sync( static_cast<char *>( arg ) );
      break;
    default:
      break;
  }
}

void tls_connection::event_handler( void *handler_arg,
                                    esp_event_base_t event_base,
                                    int32_t event_id,
                                    void *event_params )
{

}

void tls_connection::enqueue_simple_message( tls_connection_task_message msg )
{
  tls_connection_task_queue_item item = { msg, nullptr };
  xQueueSend( m_message_queue, &item, 10 );
}

void tls_connection::connection_failure( const char *msg, event event_id )
{
  ESP_LOGE( m_component_name, "Connection failure: %s", msg );
  m_event_dispatcher.dispatch( m_event_base, static_cast<int32_t>( event_id ), NULL, 1 );
}

void tls_connection::heap_report() {
  size_t free_heap_size = esp_get_free_internal_heap_size();
  size_t min_free_heap_size = esp_get_minimum_free_heap_size();
  ESP_LOGI( m_component_name, "Free heap size: %d, minimum free heap size: %d", free_heap_size, min_free_heap_size );
}

void tls_connection::init_sync()
{
  ESP_LOGI( m_component_name, "Initializing TLS connection" );

  if( m_tls ) {
    ESP_LOGI( m_component_name, "Destroy existing connection" );
    esp_tls_conn_destroy( m_tls );
    m_tls = nullptr;
  }
  
  m_cfg.cacert_buf = isrgroot_pem_start;
  m_cfg.cacert_bytes = isrgroot_pem_end - isrgroot_pem_start;

  m_tls = esp_tls_init();
  if( m_tls == nullptr ) {
    connection_failure( "Initialization not successful", event::init_failed );
    return;
  }
  std::string server_check_url = "https://50.espena.no/?token=" +
                                 std::string( m_tls_connection_token );
  if( esp_tls_conn_http_new_sync( server_check_url.c_str(), &m_cfg, m_tls ) == 1 ) {
    ESP_LOGI( m_component_name, "Connected to 50.espena.no" );
  }
  else {
    connection_failure( "Test connection not successful", event::test_conn_failed );
    if( m_session ) {
      esp_tls_free_client_session( m_session );
      m_session = nullptr;
      m_tls_initialized = false;
    }
    return;
  }

  if( m_session ) {
    esp_tls_free_client_session( m_session );
  }
  m_session = esp_tls_get_client_session( m_tls );
  m_tls_initialized = true;
  return;
}

void tls_connection::post_sync( char *json )
{
  const char *req_fmt = "POST https://50.espena.no/?token=%s HTTP/1.0\r\n"
                        "Host: 50.espena.no\r\n"
                        "User-Agent: ultimate-invitation-card esp32\r\n"
                        "Content-Type: application/json\r\n"
                        "Content-Length: %d\r\n"
                        "\r\n"
                        "%s";

  const size_t req_len = strlen( req_fmt ) +
                         strlen( m_tls_connection_token ) +
                         strlen( json ) + 10;

  char *req = new char[ req_len ];
  memset( req, 0x00, req_len );

  const size_t json_len = strlen( json );

  snprintf( req, req_len - 1, req_fmt, m_tls_connection_token, json_len, json );
  
  ESP_LOGI( m_component_name, "Sending request:\n%s", req );

  size_t offset = 0;
  const size_t end = strlen( req );

  if( m_tls == nullptr ) {
    ESP_LOGE( m_component_name, "TLS not initialized" );
    delete [] req;
    if( m_response_buffer ) {
      delete [] m_response_buffer;
      m_response_buffer = nullptr;
    }
    return;
  }

  while( offset < end ) {

    ESP_LOGI( m_component_name, "Writing chunk to server: m_tls = %d req = %d end = %d", ( int ) m_tls, ( int ) req, ( int ) end );
    int ret = esp_tls_conn_write( m_tls, req + offset, end - offset );
    
    ESP_LOGI( m_component_name, "Done writing chunk" );

    if( ret >= 0 ) {
      offset += ret;  
    }
    else if( ret == ESP_TLS_ERR_SSL_WANT_READ || ret == ESP_TLS_ERR_SSL_WANT_WRITE ) {
      continue;
    }
    else {
      ESP_LOGE( m_component_name, "Connection error: 0x%x", ret );
      break;
    }

  } // while( offset < end )
  
  delete [] req;
  
  if( offset == end ) {
    ESP_LOGI( m_component_name, "OK! Request sent, reading response" );
    std::string response = "";
    char buf[ 1024 ];
    int ret = 0;
    do {
      const size_t buf_len = sizeof( buf ) - 1;
      size_t len = buf_len - 1;
      memset( buf, 0x00, buf_len );
      ret = esp_tls_conn_read( m_tls, buf, len );
      if( ret >= 0 ) {
        len = ret;  
      }
      else if( ret == ESP_TLS_ERR_SSL_WANT_READ || ret == ESP_TLS_ERR_SSL_WANT_WRITE ) {
        continue;
      }
      else {
        break;
      }
      response += std::string( buf, len );
    } while( ret > 0 );
    ESP_LOGI( m_component_name, "Response: %s", response.c_str() );
    
    if( response.find( "200 OK" ) != std::string::npos ) {
      m_post_status = 1;
    }
    else{
      m_post_status = -1;
    }
  }
  if( m_response_buffer ) {
    delete [] m_response_buffer;
    m_response_buffer = nullptr;
  }
}

void tls_connection::init()
{
  enqueue_simple_message( tls_connection_task_message::init );
}

bool tls_connection::init_await()
{
  while( m_tls_initialized ) {
    m_tls_initialized = false;
  }
  init();
  int timeout_ms = 5000;
  while( timeout_ms > 0 && m_tls_initialized == false ) {
    vTaskDelay( 100 / portTICK_PERIOD_MS );
    timeout_ms -= 100;
  }
  return m_tls_initialized;
}

void tls_connection::post( std::string json )
{
  int timeout_ms = 10000;
  while( m_response_buffer && timeout_ms > 0 ) {
    vTaskDelay( 100 / portTICK_PERIOD_MS );
    timeout_ms -= 100;
  }
  if( m_response_buffer == nullptr ) {
    m_response_buffer = new char[ json.length() + 1 ];
    memset( m_response_buffer, 0x00, json.length() + 1 );
    memcpy( m_response_buffer, json.c_str(), json.length() );
    tls_connection_task_queue_item item = { tls_connection_task_message::post, m_response_buffer };
    xQueueSend( m_message_queue, &item, 10 );
  }
  ESP_LOGE( m_component_name, "Post failed due to timeout" );
}

bool tls_connection::post_await( std::string json ) {
  m_post_status = 0;
  int timeout_ms = 5000;
  post( json );
  while( timeout_ms > 0 && m_post_status == 0 ) {
    vTaskDelay( 100 / portTICK_PERIOD_MS );
    timeout_ms -= 100;
  }
  return m_post_status == 1; // success!
}

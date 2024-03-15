#include <memory.h>
#include "esp_timer.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_netif_sntp.h"
#include "esp_log.h"
#include "time_sync.hpp"

using namespace espena::components;

const char *time_sync::m_component_name = "time_sync";

esp_sntp_config_t time_sync::m_sntp_config = {
  .smooth_sync = false,
  .server_from_dhcp = false,
  .wait_for_sync = true,
  .start = true,
  .sync_cb = nullptr,
  .renew_servers_after_new_IP = false,
  .ip_event_to_renew = IP_EVENT_STA_GOT_IP,
  .index_of_first_server = 0,
  .num_of_servers = 1,
  .servers = { "pool.ntp.org" }
};

time_sync::time_sync() : m_nvs( 0 )
{
}

esp_err_t time_sync::fetch_time()
{
  int attempt = 0;
  const int last_attempt = 10;
  const TickType_t timeout = pdMS_TO_TICKS( 2000 );
  ESP_LOGI( m_component_name, "Fetching time from NTP server" );
  while( ++attempt != last_attempt ) {
    if( esp_netif_sntp_sync_wait( timeout ) == ESP_OK ) {
      break;
    }
    if( attempt == last_attempt ) {
      ESP_LOGE( m_component_name, "Failed to fetch time from NTP server" );
      return ESP_FAIL;
    }
  }
  return ESP_OK;
}

esp_err_t time_sync::open_nvs()
{
  esp_err_t res = nvs_open( m_component_name, NVS_READWRITE, &m_nvs );
  if( res != ESP_OK ) {
    ESP_LOGE( m_component_name, "Failed to open NVS" );
    clean_up();
    return ESP_FAIL;
  }
  return ESP_OK;
}

void time_sync::close_nvs()
{
  if( m_nvs != 0 ) {
    nvs_close( m_nvs );
    m_nvs = 0;
  }
}

void time_sync::clean_up()
{
  close_nvs();
  esp_netif_sntp_deinit();
}

void time_sync::time_nvs_put( void *arg )
{
  time_sync *inst = static_cast<time_sync *>( arg );
  inst->time_nvs_put();
}

esp_err_t time_sync::time_nvs_put()
{

  esp_err_t res;

  res = fetch_time();
  if( res != ESP_OK ) {
    clean_up();
    return ESP_FAIL;
  }

  time_t now;
  time( &now );

  if( open_nvs() != ESP_OK ) {
    return ESP_FAIL;
  }

  res = nvs_set_i64( m_nvs, "timestamp", now );
  if( res != ESP_OK ) {
    ESP_LOGE( m_component_name, "Failed to write time to NVS" );
    clean_up();
    return ESP_FAIL;
  }

  res = nvs_commit( m_nvs );
  if( res != ESP_OK ) {
    ESP_LOGE( m_component_name, "Failed to commit changes to NVS" );
    clean_up();
    return ESP_FAIL;
  }
  ESP_LOGI( m_component_name, "Time written to NVS" );

  clean_up();
  return ESP_OK;
}

esp_err_t time_sync::time_nvs_get()
{

  esp_err_t res;

  if( open_nvs() != ESP_OK ) {
    return ESP_FAIL;
  }

  int64_t timestamp;
  
  res = nvs_get_i64( m_nvs, "timestamp", &timestamp );
  if( res == ESP_ERR_NVS_NOT_FOUND ) {
    clean_up(); // NVS not found, write current time
    return time_nvs_put();
  }
  else if( res != ESP_OK ) {
    ESP_LOGE( m_component_name, "Failed to read NVS" );
    clean_up();
    return ESP_FAIL;
  }

  return ESP_OK;
}

void time_sync::init()
{

  ESP_LOGI( m_component_name, "Initializing NTP time sync service" );
  
  esp_netif_sntp_init( &m_sntp_config );

  if( time_nvs_put() == ESP_OK ) {
    ESP_LOGI( m_component_name, "Time updated" );
  }

  esp_timer_handle_t timer_handle = nullptr;
  esp_timer_create_args_t timer_args;

  memset( &timer_args, 0x00, sizeof( timer_args ) );
  timer_args.callback = time_nvs_put;
  timer_args.arg = this;

  ESP_ERROR_CHECK( esp_timer_create( &timer_args, &timer_handle ) );
  ESP_ERROR_CHECK( esp_timer_start_periodic( timer_handle, 43200000000ULL ) );
}

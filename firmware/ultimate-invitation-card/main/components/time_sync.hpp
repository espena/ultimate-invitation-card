#ifndef __time_sync_hpp__
#define __time_sync_hpp__

#include <freertos/FreeRTOS.h>
#include "nvs_flash.h"
#include "esp_netif_sntp.h"
#include "esp_tls.h"

namespace espena::components {

  class time_sync {

    static esp_sntp_config_t m_sntp_config;

    static esp_err_t fetch_time();

    nvs_handle_t m_nvs;

    esp_err_t open_nvs();
    void close_nvs();

    esp_err_t time_nvs_get();
    
    static void time_nvs_put( void *arg );
    esp_err_t time_nvs_put();

    void clean_up();

  public:

    static const char *m_component_name;

    time_sync();

    void init();  
  
  }; // class time_sync

}; // namespace espena::components

#endif // __time_sync_hpp__
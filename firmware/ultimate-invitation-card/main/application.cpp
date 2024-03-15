#include <map>
#include <memory.h>
#include <driver/gpio.h>
#include "driver/adc.h"
#include "rom/rtc.h"
#include "nvs_flash.h"
#include "esp_wifi.h"
#include <esp_log.h>
#include <esp_event.h>
#include "components/i_playbook.hpp"
#include "components/playbook.hpp"
#include "components/pwm.hpp"
#include "components/captive_portal_wifi.hpp"
#include "rundown/i_rundown.hpp"
#include "rundown/intro_rundown.hpp"
#include "rundown/intro_coming_rundown.hpp"
#include "rundown/intro_not_coming_rundown.hpp"
#include "rundown/respond_rundown.hpp"
#include "rundown/respond_with_wifi_intro_rundown.hpp"
#include "rundown/respond_with_wifi_rundown.hpp"
#include "rundown/respond_provision_and_amend_rundown.hpp"
#include "rundown/respond_amend_rundown.hpp"
#include "rundown/countdown_rundown.hpp"
#include "rundown/wifi_rundown.hpp"
#include "rundown/wifi_provisioning_rundown.hpp"
#include "rundown/wifi_disconnected_rundown.hpp"
#include "rundown/wifi_login_rundown.hpp"
#include "rundown/wifi_login_failure_rundown.hpp"
#include "rundown/wifi_ap_not_found_rundown.hpp"
#include "rundown/main_menu_rundown.hpp"
#include "rundown/main_menu_responded_rundown.hpp"
#include "rundown/main_menu_not_sent_rundown.hpp"
#include "rundown/mnu_change_response_rundown.hpp"
#include "rundown/info_rundown.hpp"
#include "rundown/info_more_rundown.hpp"
#include "rundown/time_rundown.hpp"
#include "rundown/venue_rundown.hpp"
#include "rundown/qrcode_rundown.hpp"
#include "rundown/clothing_rundown.hpp"
#include "rundown/transport_rundown.hpp"
#include "rundown/transport_to_rundown.hpp"
#include "rundown/transport_from_rundown.hpp"
#include "rundown/bring_rundown.hpp"
#include "rundown/address_rundown.hpp"
#include "rundown/wee_rundown.hpp"
#include "rundown/happy_roller_rundown.hpp"
#include "rundown/neei_rundown.hpp"
#include "rundown/sad_roller_rundown.hpp"
#include "rundown/unable_to_send_rundown.hpp"
#include "rundown/website_url_rundown.hpp"
#include "rundown/sending_to_server_rundown.hpp"
#include "rundown/low_battery_rundown.hpp"
#include "rundown/nvs_deleted_rundown.hpp"
#include "application.hpp"
#include "p13n.hpp"

using namespace espena;

const char application::m_component_name[] = "application";
application * application::m_the_app = nullptr;

application * application::get() {
  if( application::m_the_app == nullptr ) {
    application::m_the_app = new application();
  }
  return application::m_the_app;
}

application::application() : m_led_btn_a( GPIO_NUM_19, "buttons" ),
                             m_led_btn_b( GPIO_NUM_2, "buttons" ),
                             m_led_btn_c( GPIO_NUM_18, "buttons" ),
                             m_led_btn_d( GPIO_NUM_23, "buttons" ),
                             m_led_btn_red( GPIO_NUM_25, "jumpers" ),
                             m_led_btn_green( GPIO_NUM_21, "jumpers" ),
                             m_beeper( GPIO_NUM_32, "beeper" ),
                             m_current_playbook( nullptr ),
                             m_pb_intro( &m_oled_display, "intro" ),
                             m_pb_intro_coming( &m_oled_display, "intro_coming" ),
                             m_pb_intro_not_coming( &m_oled_display, "intro_not_coming" ),
                             m_pb_main_menu( &m_oled_display, "main_menu" ),
                             m_pb_main_menu_responded( &m_oled_display, "main_menu_responded" ),
                             m_pb_main_menu_not_sent( &m_oled_display, "main_menu_not_sent" ),
                             m_pb_mnu_change_response( &m_oled_display, "mnu_change_response" ),
                             m_pb_info( &m_oled_display, "info" ),
                             m_pb_info_more( &m_oled_display, "info_more" ),
                             m_pb_respond( &m_oled_display, "respond" ),
                             m_pb_respond_with_wifi_intro( &m_oled_display, "respond_with_wifi_intro" ),
                             m_pb_respond_with_wifi( &m_oled_display, "respond_with_wifi" ),
                             m_pb_respond_provision_and_amend( &m_oled_display, "respond_provision_and_amend" ),
                             m_pb_respond_amend( &m_oled_display, "respond_amend" ),
                             m_pb_countdown( &m_oled_display, "countdown" ),
                             m_pb_wifi( &m_oled_display, "wifi" ),
                             m_pb_wifi_provisioning( &m_oled_display, "wifi_provisioning" ),
                             m_pb_wifi_disconnected( &m_oled_display, "wifi_disconnected" ),
                             m_pb_wifi_login( &m_oled_display, "wifi_login" ),
                             m_pb_wifi_login_failure( &m_oled_display, "wifi_login_failure" ),
                             m_pb_wifi_ap_not_found( &m_oled_display, "wifi_ap_not_found" ),
                             m_pb_time( &m_oled_display, "time" ),
                             m_pb_venue( &m_oled_display, "venue" ),
                             m_pb_address( &m_oled_display, "address" ),
                             m_pb_qrcode( &m_oled_display, "qrcode" ),
                             m_pb_clothing( &m_oled_display, "clothing" ),
                             m_pb_transport( &m_oled_display, "transport" ),
                             m_pb_transport_to( &m_oled_display, "transport_to" ),
                             m_pb_transport_from( &m_oled_display, "transport_from" ),
                             m_pb_bring( &m_oled_display, "bring" ),
                             m_pb_wee( &m_oled_display, "wee" ),
                             m_pb_happy_roller( &m_oled_display, "happy_roller" ),
                             m_pb_neei( &m_oled_display, "neei" ),
                             m_pb_sad_roller( &m_oled_display, "sad_roller" ),
                             m_pb_unable_to_send( &m_oled_display, "unable_to_send" ),
                             m_pb_website_url( &m_oled_display, "website_url" ),
                             m_pb_sending_to_server( &m_oled_display, "sending_to_server" ),
                             m_pb_low_battery( &m_oled_display, "low_battery" ),
                             m_pb_nvs_deleted( &m_oled_display, "nvs_deleted" ) {

  init_inputs();

  m_processing_wire_cut = false;
  m_sending_to_server = false;
  m_wifi_connected = false;
  m_changed_wire = cuttable_wire::none;

  m_oled_display.clear();

  // Get saved settings
  int8_t val;
  nvs_handle_t nvs = 0;
  nvs_open( m_component_name, NVS_READONLY, &nvs );
  if( nvs ) {

    val = 0;
    nvs_get_i8( nvs, "did_respond", &val );
    ESP_LOGI( m_component_name, "did_respond: %d", val );
    m_did_respond = ( val == 0x01 );

    val = 0;
    nvs_get_i8( nvs, "is_coming", &val );
    ESP_LOGI( m_component_name, "is_coming: %d", val );
    m_is_coming = ( val == 0x01 );

    val = 0;
    nvs_get_i8( nvs, "wifi_configured", &val );
    ESP_LOGI( m_component_name, "wifi_configured: %d", val );
    m_wifi_configured = ( val == 0x01 );

    nvs_close( nvs );
    nvs = 0;
  }
  else {
    m_did_respond = false;
    m_is_coming = false;
    m_wifi_configured = false;
  }

  if( m_did_respond ) {
    ESP_LOGI( m_component_name, "Client has already responded" );
  }
  else {
    ESP_LOGI( m_component_name, "Client has not yet responded" );
  }

  m_message_queue = xQueueCreate( 50, sizeof( application_task_queue_item ) );

  application::m_the_app = this;
  esp_event_loop_args_t loop_args = {
    .queue_size = 1000,
    .task_name = "loop_task",
    .task_priority = uxTaskPriorityGet( NULL ),
    .task_stack_size = 8192,
    .task_core_id = tskNO_AFFINITY
  };

  esp_event_loop_create( &loop_args, &m_event_loop_handle );

  m_cuttable_wire_watcher.set_event_loop_handle( m_event_loop_handle );

  m_cuttable_wire_watcher.add_event_listener( ::espena::components::cuttable_wire_watcher::event::wire_recently_cut,
                                              event_handler );

  m_cuttable_wire_watcher.add_event_listener( ::espena::components::cuttable_wire_watcher::event::wire_previously_cut,
                                              event_handler );

  m_power_timeout.set_event_loop_handle( m_event_loop_handle );

  m_power_timeout.add_event_listener( ::espena::components::power_timeout::event::timeout,
                                      event_handler );

  m_captive_portal.add_event_listener( ::espena::components::captive_portal_wifi::event::network_connecting,
                                       event_handler,
                                       this );

  m_captive_portal.add_event_listener( ::espena::components::captive_portal_wifi::event::network_ready,
                                       event_handler,
                                       this );

  m_captive_portal.add_event_listener( ::espena::components::captive_portal_wifi::event::client_connected,
                                       event_handler,
                                       this );

  m_captive_portal.add_event_listener( ::espena::components::captive_portal_wifi::event::provisioning_required,
                                       event_handler,
                                       this );

  m_captive_portal.add_event_listener( ::espena::components::captive_portal_wifi::event::provisioning_aborted,
                                       event_handler,
                                       this );

  m_captive_portal.add_event_listener( ::espena::components::captive_portal_wifi::event::sta_disconnected,
                                       event_handler,
                                       this );

  m_captive_portal.add_event_listener( ::espena::components::captive_portal_wifi::event::login_failure,
                                       event_handler,
                                       this );

  m_captive_portal.add_event_listener( ::espena::components::captive_portal_wifi::event::ap_not_found,
                                       event_handler,
                                       this );

  m_captive_portal.add_event_listener( ::espena::components::captive_portal_wifi::event::got_ip,
                                       event_handler,
                                       this );
  init_playbooks();

  // Delete non-volatile storage if D button is pressed during boot
  if( gpio_get_level( GPIO_NUM_13 ) == 0 ) {
    erase_none_volatile_storage();
    shutdown();
  }
}

void application::erase_none_volatile_storage() {
  components::pwm::breathe( "buttons" );
  components::pwm::breathe( "jumpers" );
  ESP_LOGI( m_component_name, "Deleting non-volatile storage" );
  if( m_current_playbook ) {
    m_current_playbook->reset();
  }
  run_playbook( &m_pb_nvs_deleted );
  nvs_flash_deinit(); // default partition
  nvs_flash_erase();
  nvs_flash_init();
  nvs_flash_deinit_partition( m_component_name ); // application partition
  nvs_flash_erase_partition( m_component_name );
  nvs_flash_init_partition( m_component_name );
  while( gpio_get_level( GPIO_NUM_13 ) == 0 ) {
    vTaskDelay( 100 / portTICK_PERIOD_MS );
  }
  vTaskDelay( 5000 / portTICK_PERIOD_MS );
}

void application::init_inputs() {

  // Power button (manual off switch)
  esp_rom_gpio_pad_select_gpio( GPIO_NUM_36 );
  gpio_set_direction( GPIO_NUM_36, GPIO_MODE_INPUT );
  gpio_pullup_dis( GPIO_NUM_36 );
  gpio_pulldown_dis( GPIO_NUM_36 );

  // Red cuttable wire
  esp_rom_gpio_pad_select_gpio( GPIO_NUM_34 );
  gpio_set_direction( GPIO_NUM_34, GPIO_MODE_INPUT );
  gpio_pullup_en( GPIO_NUM_34 );
  gpio_pulldown_dis( GPIO_NUM_34 );

  // Green cuttable wire
  esp_rom_gpio_pad_select_gpio( GPIO_NUM_35 );
  gpio_set_direction( GPIO_NUM_35, GPIO_MODE_INPUT );
  gpio_pullup_en( GPIO_NUM_35 );
  gpio_pulldown_dis( GPIO_NUM_35 );

  // Menu buttons
  init_button_input( GPIO_NUM_26 );
  init_button_input( GPIO_NUM_14 );
  init_button_input( GPIO_NUM_22 );
  init_button_input( GPIO_NUM_13 );
  gpio_set_direction( GPIO_NUM_33, GPIO_MODE_OUTPUT );
  gpio_set_level( GPIO_NUM_33, 0 );

}

void application::run_playbook( ::espena::i_playbook *playbook ) {
  ESP_LOGI( m_component_name, "Running playbook '%s'", playbook->name().c_str() );
  m_current_playbook = playbook;
  m_current_playbook->run();
}

void application::run_intro() {
  if( m_did_respond ) {
    ESP_LOGI( m_component_name, "Client has responded" );
    if( m_is_coming ) {
      ESP_LOGI( m_component_name, "Client is coming to the party" );
      run_playbook( &m_pb_intro_coming );
    }
    else {
      ESP_LOGI( m_component_name, "Client is NOT coming to the party" );
      run_playbook( &m_pb_intro_not_coming );
    }
  }
  else {
    ESP_LOGI( m_component_name, "Client has not yet responded" );
    run_playbook( &m_pb_intro );
  }
}

void application::run_main_menu() {
  if( m_did_respond ) {
    run_playbook( &m_pb_main_menu_responded );
  }
  else {
    run_playbook( &m_pb_main_menu );
  }
}

void application::set_button_interrupts() {
  gpio_num_t buttons[ ] = { GPIO_NUM_26, GPIO_NUM_14, GPIO_NUM_22, GPIO_NUM_13, GPIO_NUM_36 };
  for( auto b : buttons ) {
    gpio_set_intr_type( b, b == GPIO_NUM_36 ? GPIO_INTR_POSEDGE : GPIO_INTR_NEGEDGE );
    gpio_intr_disable( b );
    gpio_intr_enable( b );
  }
}

void application::on_gpio() {
  ESP_LOGI( m_component_name, "GPIO interrupt" );
  application_task_queue_item item;
  if( gpio_get_level( GPIO_NUM_36 ) == 1 ) {
    item.message = application_task_message::off;
    item.arg = nullptr;
    xQueueSend( m_message_queue, &item, portMAX_DELAY );
  }
  else {
    m_power_timeout.reset();
    set_button_interrupts();
  }
}

void application::gpio_isr( void *arg ) {
  application *app = static_cast<application *>( arg );
  application_task_queue_item item;
  memset( &item, 0x00, sizeof( application_task_queue_item ) );
  item.message = application_task_message::gpio;
  xQueueSend( app->m_message_queue, &item, 0 );
}

void application::init_button_input( gpio_num_t gpio_num ) {
  gpio_set_direction( gpio_num, GPIO_MODE_INPUT );
  gpio_pulldown_dis( gpio_num );
  gpio_pullup_en( gpio_num );
}

void application::event_handler( void *handler_arg,
                                 esp_event_base_t event_base,
                                 int32_t event_id,
                                 void *event_params )
{
  const std::string source = ( char * ) event_base;
  if( source == ( char * ) ::espena::components::playbook::m_event_base ) {
    application::m_the_app->event_handler_playbook( static_cast<::espena::components::playbook::event>( event_id ), event_params );
  }
  else if( source == ( char * ) ::espena::components::cuttable_wire_watcher::m_event_base ) {
    application::m_the_app->event_handler_cuttable_wire( static_cast<::espena::components::cuttable_wire_watcher::event>( event_id ),
                                                         *static_cast<::espena::cuttable_wire *>( event_params ) );
  }
  else if( source == ( char * ) ::espena::components::power_timeout::m_event_base ) {
    application::m_the_app->event_handler_power_timeout( static_cast<::espena::components::power_timeout::event>( event_id ) );
  }
  else if( source == ( char * ) ::espena::components::captive_portal_wifi::m_event_base ) {
    application::m_the_app->event_handler_captive_portal_wifi( static_cast<::espena::components::captive_portal_wifi::event>( event_id ) );
  }
}

void application::event_handler_playbook( ::espena::components::playbook::event event_id,
                                          void *event_params ) {
  switch( event_id ) {
    case ::espena::components::playbook::event::menu_prompt:
      on_menu_prompt( static_cast<::espena::playbook_item *>( event_params ) );
      break;
    case ::espena::components::playbook::event::cuttable_wire:
      on_cuttable_wire( *static_cast<::espena::cuttable_wire *>( event_params ) );
      break;
    case ::espena::components::playbook::event::beep:
      switch( *static_cast<int *>( event_params ) ) {
        case 3: m_beeper.beeeep(); break;
        case 2: m_beeper.beeep(); break;
        default: m_beeper.beep();
      }
      break;
    case ::espena::components::playbook::event::menu_select:
      on_menu_select( *static_cast<::espena::menu_select *>( event_params ) );
      break;
    case ::espena::components::playbook::event::play_finished:
      on_playbook_finished( static_cast<::espena::components::playbook *>( event_params ) );
      break;
    case ::espena::components::playbook::event::play_reset:
      on_playbook_reset( static_cast<::espena::components::playbook *>( event_params ) );
      break;
    default:
      ESP_LOGI( m_component_name, "Unknown event id" );
      break;
  }
}

bool application::test_network_connection() {
  return m_tls_connection.post_await( "{\"name\":\"" + std::string( P13N_NAME ) + "\",\"action\":\"test\"}" );
}

void application::wait_for_flag( bool &flag, uint32_t timeout_ms ) {
  while( timeout_ms > 0 && flag == false ) {
    vTaskDelay( 100 / portTICK_PERIOD_MS );
    timeout_ms -= 100;
  }
}

void application::set_nvs_respond_flags( espena::cuttable_wire wire ) {
  nvs_handle_t nvs = 0;
  m_is_coming = wire == espena::cuttable_wire::green ? 0x01 : 0x00;
  m_did_respond = true;
  ESP_ERROR_CHECK( nvs_open( m_component_name, NVS_READWRITE, &nvs ) );
  ESP_ERROR_CHECK( nvs_set_i8( nvs, "did_respond", m_did_respond ) );
  ESP_ERROR_CHECK( nvs_set_i8( nvs, "is_coming", m_is_coming ) );
  ESP_ERROR_CHECK( nvs_commit( nvs ) );
                    nvs_close( nvs );
                    nvs = 0;
}

bool application::send_response_to_server( espena::cuttable_wire wire ) {

        std::string str_wire = ( wire == espena::cuttable_wire::red
                                  ? "red"
                                  : "green" );

        std::string json = "{\"name\":\"" + std::string( P13N_NAME ) +
                          "\",\"action\":\"wire_cut\",\"wire\":\"" +
                          str_wire +
                          "\"}";

        ESP_LOGI( m_component_name, "WiFi connected! Posting to server..." );
        
        if( !m_wifi_connected ) {
          ESP_LOGI( m_component_name, "WiFi connection failed" );
          return false;
        }
        
        if( !m_tls_connection.init_await() ) {
          ESP_LOGI( m_component_name, "TLS connection initialization failed" );
          return false;
        }
        
        ESP_LOGI( m_component_name, "TLS connection initialized" );
        bool success = m_tls_connection.post_await( json );
        
        if( !success ) {
          ESP_LOGI( m_component_name, "Server did not respond with OK" );
          return false;
        }
        
        ESP_LOGI( m_component_name, "Server responded with OK" );
        set_nvs_respond_flags( wire );
        m_did_respond = true;
        m_sending_to_server = false;
        
        return true;
}

void application::event_handler_cuttable_wire( ::espena::components::cuttable_wire_watcher::event event_id, espena::cuttable_wire wire ) {

  switch( event_id ) {
    case ::espena::components::cuttable_wire_watcher::event::wire_previously_cut:
      // Fallthrough
    case ::espena::components::cuttable_wire_watcher::event::wire_recently_cut:
      if( !m_did_respond ) {
        m_processing_wire_cut = true;
        if( m_current_playbook ) {
          ESP_LOGI( m_component_name, "Resetting current playbook '%s'", m_current_playbook->name().c_str() );
          m_current_playbook->reset();
        }
        espena::components::playbook *pb = nullptr;
        if( wire == espena::cuttable_wire::green ) {
          ESP_LOGI( m_component_name, "Starting 'weeee' playbook" );
          pb = &m_pb_wee;
        }
        else {
          ESP_LOGI( m_component_name, "Starting 'noooo' playbook" );
          pb = &m_pb_neei;
        }
        run_playbook( pb );
        vTaskDelay( 5000 / portTICK_PERIOD_MS );
        if( m_wifi_configured ) {
          bool success = send_response_to_server( wire );
          if( success ) {
            pb->resume();
          }
          else {
            pb->reset();
            ESP_LOGE( m_component_name, "Unable to send sent from wire_recently_cut" );
            run_playbook( &m_pb_unable_to_send );
          }
        }
        else {
          pb->reset();
          run_playbook( &m_pb_wifi_provisioning );
          m_captive_portal.start();
        }
      }
      break;
    default:
      ESP_LOGI( m_component_name, "Unknown event id" );
      break;
  }
}
void application::event_handler_power_timeout( ::espena::components::power_timeout::event event_id ) {
  switch( event_id ) {
    case ::espena::components::power_timeout::event::timeout:
      m_beeper.beeeep();
      vTaskDelay( 3000 / portTICK_PERIOD_MS );
      shutdown();
      break;
    default:
      ESP_LOGI( m_component_name, "Unknown event id" );
      break;
  }
}

void application::set_wifi_status( bool is_connected ) {
  m_wifi_connected = is_connected;
  m_wifi_configured = is_connected;
  nvs_handle nvs = 0;
  nvs_flash_init();
  nvs_open( m_component_name, NVS_READWRITE, &nvs );
  nvs_set_i8( nvs, "wifi_configured", m_wifi_configured ? 0x01 : 0x00 );
  nvs_commit( nvs );
  nvs_close( nvs );
}

void application::event_handler_captive_portal_wifi( ::espena::components::captive_portal_wifi::event event_id ) {
  m_power_timeout.reset();
  std::string json;
  switch( event_id ) {
    case ::espena::components::captive_portal_wifi::event::network_connecting:
      m_beeper.beep();
      m_pb_wifi_provisioning.reset();
      run_playbook( &m_pb_wifi_login );
      break;
    case ::espena::components::captive_portal_wifi::event::network_ready:
      ESP_LOGI( m_component_name, "Network ready, playbook: %s", m_current_playbook ? m_current_playbook->name().c_str() : "[no playbook]" );
      if( m_current_playbook != nullptr && ( m_current_playbook->name() == "wifi_provisioning" ) ) {
        vTaskDelay( 2000 / portTICK_PERIOD_MS ); // Wait a bit, to allow user to read display message
        ESP_LOGI( m_component_name, "Resume playbook for WiFi provisioning" );
        m_pb_wifi_provisioning.resume(); // < Should have a parameter indicating status of operation
      }
      break;
    case ::espena::components::captive_portal_wifi::event::client_connected:
      ESP_LOGI( m_component_name, "Client connected, playbook: %s", m_current_playbook ? m_current_playbook->name().c_str() : "[no playbook]" );
      if( m_current_playbook != nullptr && m_current_playbook->name() == "wifi_provisioning" ) {
        m_pb_wifi_provisioning.resume();
        m_beeper.beeep();
      }
      break;
    case ::espena::components::captive_portal_wifi::event::sta_disconnected:
      m_wifi_connected = false;
      break;
    case ::espena::components::captive_portal_wifi::event::login_failure:
      ESP_LOGE( m_component_name, "Login failure" );
      m_beeper.beeep();
      m_pb_wifi_login.reset();
      run_playbook( &m_pb_wifi_login_failure );
      m_captive_portal.stop();
      break;
    case ::espena::components::captive_portal_wifi::event::ap_not_found:
      ESP_LOGW( m_component_name, "AP not found (%s)", m_current_playbook ? m_current_playbook->name().c_str() : "[no playbook]" );
      if( m_current_playbook && m_current_playbook->name() == "sending_to_server" ) {
        m_sending_to_server = true;
        m_captive_portal.stop();
        m_current_playbook->reset();
        run_playbook( &m_pb_wifi_provisioning );
        vTaskDelay( 2000 / portTICK_PERIOD_MS );
        m_captive_portal.start();
      }
      else {
        m_beeper.beeep();
        m_pb_wifi_login.reset();
        run_playbook( &m_pb_wifi_ap_not_found );
        m_captive_portal.stop();
      }
      break;
    case ::espena::components::captive_portal_wifi::event::got_ip:
      ESP_LOGW( m_component_name, "----> Received IP address from DHCP: %s <-----", m_current_playbook ? m_current_playbook->name().c_str() : "[no playbook]" );
      set_wifi_status( true );
      m_time_sync.init();
      if( m_current_playbook && m_current_playbook->name() == "wifi_login" ) {
        ESP_LOGW( m_component_name, "----> Resume wifi_login book: %s <-----", m_current_playbook ? m_current_playbook->name().c_str() : "[no playbook]" );
        m_current_playbook->reset();
        if( m_processing_wire_cut ) {
          ESP_LOGW( m_component_name, "----> Sending response to server <-----" );
          ::espena::cuttable_wire wire = m_cuttable_wire_watcher.cutted_wire();
          int success = send_response_to_server( wire );
          if( success ) {
            run_playbook( wire == cuttable_wire::green ? &m_pb_happy_roller
                                                       : &m_pb_sad_roller );
          }
          else {
            ESP_LOGE( m_component_name, "Unable to send response to server sent from got_ip event!" );
            run_playbook( &m_pb_unable_to_send );
          }
          m_processing_wire_cut = false;
        }
        else if( m_changed_wire != cuttable_wire::none ) {
          int success = send_response_to_server( m_changed_wire );
          if( success ) {
            run_playbook( m_changed_wire == cuttable_wire::green ? &m_pb_happy_roller
                                                                 : &m_pb_sad_roller );
          }
          else {
            ESP_LOGE( m_component_name, "Unable to send changed response to server" );
            run_playbook( &m_pb_unable_to_send );
          }
        }
        else {
          run_playbook( &m_pb_respond_with_wifi_intro );
        }
      }
      else if( m_current_playbook && m_current_playbook->name() == "sending_to_server") {
        m_sending_to_server = true;
        ESP_LOGW( m_component_name, "----> Resume changing response <----" ); 
        m_current_playbook->reset();
        if( m_changed_wire != cuttable_wire::none ) {
          ESP_LOGW( m_component_name, "----> m_changed_wire detected! <----" );
          int success = send_response_to_server( m_changed_wire  );
          if( success ) {
            run_playbook( m_changed_wire == cuttable_wire::green ? &m_pb_happy_roller
                                                                  : &m_pb_sad_roller );
          }
          else {
            ESP_LOGE( m_component_name, "Unable to send response to server sent from got_ip event!" );
            run_playbook( &m_pb_unable_to_send );
          }
        }
      }
      break;
    case ::espena::components::captive_portal_wifi::event::provisioning_required:
      ESP_LOGI( m_component_name, "Provisioning required" );
      if( m_current_playbook ) {
        m_current_playbook->reset();
      }
      run_playbook( &m_pb_wifi_provisioning );
      m_captive_portal.start();
      break;
    case ::espena::components::captive_portal_wifi::event::provisioning_aborted:
      ESP_LOGI( m_component_name, "Provisioning aborted" );
      m_wifi_connected = false;
      m_beeper.beeep();
      m_pb_wifi_provisioning.reset();
      run_playbook( &m_pb_wifi_disconnected );
      break;
    default:
      break;
  } 
}

void application::on_menu_prompt( ::espena::playbook_item *playbook_item ) {
  // Indicate valid menu button choices
  components::pwm *leds[ 4 ] = { &m_led_btn_a, &m_led_btn_b, &m_led_btn_c, &m_led_btn_d };
  for( auto i = 0; i < 4; i++ ) {
    if( playbook_item == nullptr ) {
      leds[ i ]->stop_breathe();
    }
    else if( playbook_item->params.event[ i ] != ::espena::menu_select::none ) {
      leds[ i ]->breathe();
    }
  }
}

void application::on_cuttable_wire( cuttable_wire wire ) {
  
  ESP_LOGI( m_component_name, "Cuttable wire: %d", static_cast<uint8_t>( wire ) );
  
  if( static_cast<bool>( wire & cuttable_wire::red ) ) {
    m_led_btn_red.on();
  }
  else {
    m_led_btn_red.off();
  }
  if( static_cast<bool>( wire & cuttable_wire::green ) ) {
    m_led_btn_green.on();
  }
  else {
    m_led_btn_green.off();
  }
}

void application::transmit_to_server( cuttable_wire wire ) {
  m_processing_wire_cut = true;
  if( m_wifi_configured ) {
    bool success = send_response_to_server( wire );
    if( success ) {
      run_playbook( wire == ::espena::cuttable_wire::green ? &m_pb_happy_roller
                                                            : &m_pb_sad_roller );
    }
    else {
      ESP_LOGE( m_component_name, "Unable to send sent from transmit_to_server" );
      run_playbook( &m_pb_unable_to_send );
    }
  }
  else {
    m_sending_to_server = true;
    run_playbook( &m_pb_wifi_provisioning );
    m_captive_portal.start();
  }
}

void application::change_response( cuttable_wire wire ) {
  run_playbook( &m_pb_sending_to_server );
  m_changed_wire = wire;
  set_nvs_respond_flags( m_changed_wire );
  m_captive_portal.stop();
  vTaskDelay( 3000 / portTICK_PERIOD_MS );
  set_wifi_status( false );
  m_captive_portal.wifi_connect();
}

void application::on_menu_select( ::espena::menu_select menu_selection ) {
  components::pwm::stop_breathe( "buttons" );
  m_beeper.beep();
  switch( menu_selection ) {
    case ::espena::menu_select::main:
      ESP_LOGI( m_component_name, "Main menu" );
      m_captive_portal.stop(); // < In case user interrupted provisioning process
      run_main_menu();
      break;
    case ::espena::menu_select::info:
      ESP_LOGI( m_component_name, "Info menu" );
      run_playbook( &m_pb_info );
      break;
    case ::espena::menu_select::info_more:
      ESP_LOGI( m_component_name, "Info more menu" );
      run_playbook( &m_pb_info_more );
      break;
    case ::espena::menu_select::time:
      ESP_LOGI( m_component_name, "Time menu" );
      run_playbook( &m_pb_time );
      break;
    case ::espena::menu_select::venue:
      ESP_LOGI( m_component_name, "Venue menu" );
      run_playbook( &m_pb_venue );
      break;
    case ::espena::menu_select::address:
      ESP_LOGI( m_component_name, "Address select" );
      run_playbook( &m_pb_address );
      break;
    case ::espena::menu_select::map:
      ESP_LOGI( m_component_name, "Map select" );
      run_playbook( &m_pb_qrcode );
      break;
    case ::espena::menu_select::clothing:
      ESP_LOGI( m_component_name, "Clothing select" );
      run_playbook( &m_pb_clothing );
      break;
    case ::espena::menu_select::transport:
      ESP_LOGI( m_component_name, "Transport select" );
      run_playbook( &m_pb_transport );
      break;
    case ::espena::menu_select::transport_to:
      ESP_LOGI( m_component_name, "Transport TO select" );
      run_playbook( &m_pb_transport_to );
      break;
    case ::espena::menu_select::transport_from:
      ESP_LOGI( m_component_name, "Transport FROM select" );
      run_playbook( &m_pb_transport_from );
      break;
    case ::espena::menu_select::bring:
      ESP_LOGI( m_component_name, "Bring-along select" );
      run_playbook( &m_pb_bring );
      break;
    case ::espena::menu_select::ready_to_respond:
      ESP_LOGI( m_component_name, "Respond with WiFi menu" );
      m_led_btn_red.timed( 12000, 6000 );
      m_led_btn_green.timed( 20500, 7000 );
      run_playbook( &m_pb_respond_with_wifi );
      break;
    case ::espena::menu_select::respond:
      ESP_LOGI( m_component_name, "Respond menu" );
      if( m_did_respond ) {
        if( m_wifi_configured ) {
          run_playbook( &m_pb_respond_amend );
        }
        else {
          run_playbook( &m_pb_respond_provision_and_amend );
        }
      }
      else {
        run_playbook( &m_pb_respond );
      }
      break;
    case ::espena::menu_select::change_response:
      run_playbook( &m_pb_mnu_change_response );
      break;
    case ::espena::menu_select::change_to_not_coming:
      change_response( cuttable_wire::red );
      break;
    case ::espena::menu_select::change_to_is_coming:
      change_response( cuttable_wire::green );
      break;
    case ::espena::menu_select::send_response:
      if( m_cuttable_wire_watcher.cutted_wire() != cuttable_wire::none ) {
        transmit_to_server( m_cuttable_wire_watcher.cutted_wire() );
      }
      else {
        if( m_did_respond ) {
          run_playbook( &m_pb_main_menu_responded );
        }
        else {
          run_playbook( &m_pb_main_menu_not_sent );
        }
      }
      break;
    case ::espena::menu_select::countdown:
      ESP_LOGI( m_component_name, "Wire cut countdown" );
      run_playbook( &m_pb_countdown );
      break;
    case ::espena::menu_select::wee:
      ESP_LOGI( m_component_name, "Replay invitation accepted" );
      run_playbook( &m_pb_wee );
      m_pb_wee.resume();
      break;
    case ::espena::menu_select::website_url:
      ESP_LOGI( m_component_name, "Website URL" );
      run_playbook( &m_pb_website_url );
      break;
    case ::espena::menu_select::wifi_provisioning:
      ESP_LOGI( m_component_name, "Wifi provisioning menu" );
      run_playbook( &m_pb_wifi_provisioning );
      m_captive_portal.start(); // Playbook will resume after client connects
      // Should add a timeout here
      break;
    case ::espena::menu_select::help:
      ESP_LOGI( m_component_name, "Help menu" );
      break;
    case ::espena::menu_select::restart:
      restart();
      break;
    case ::espena::menu_select::shutdown:
      shutdown();
      break;
    default:
      ESP_LOGI( m_component_name, "Unknown menu selection" );
      restart();
      break;
  }
}

void application::on_playbook_finished( ::espena::components::playbook *playbook ) {
  ESP_LOGI( m_component_name, "Playbook finished: %s", playbook->get_name().c_str() );
  if( playbook->get_name() == "low_battery" ) {
    run_main_menu();
  }
  if( playbook->get_name() == "intro" ) {
    run_main_menu();
  }
  if( playbook->get_name() == "countdown" ) {
    run_main_menu();
  }
  if( playbook->get_name() == "neei" ) {
    if( m_did_respond ) {
      run_playbook( &m_pb_sad_roller );
    }
    else {
      ESP_LOGE( m_component_name, "Unable to send sent from plabbook_finished ( neei )" );
      run_playbook( &m_pb_unable_to_send );
    }
  }
  if( playbook->get_name() == "wee" ) {
    if( m_did_respond ) {
      run_playbook( &m_pb_happy_roller );
    }
    else {
      ESP_LOGE( m_component_name, "Unable to send sent from plabbook_finished ( weee )" );
      run_playbook( &m_pb_unable_to_send );
    }
  }
}

void application::on_playbook_reset( ::espena::components::playbook *playbook ) {
  ESP_LOGI( m_component_name, "Playbook reset" );
}

void application::init_playbooks() {
  init_playbook<::espena::intro_rundown>                       ( &m_pb_intro                       );
  init_playbook<::espena::intro_coming_rundown>                ( &m_pb_intro_coming                );
  init_playbook<::espena::intro_not_coming_rundown>            ( &m_pb_intro_not_coming            );
  init_playbook<::espena::info_rundown>                        ( &m_pb_info                        );
  init_playbook<::espena::info_more_rundown>                   ( &m_pb_info_more                   );
  init_playbook<::espena::respond_rundown>                     ( &m_pb_respond                     );
  init_playbook<::espena::respond_with_wifi_intro_rundown>     ( &m_pb_respond_with_wifi_intro     );
  init_playbook<::espena::respond_with_wifi_rundown>           ( &m_pb_respond_with_wifi           );
  init_playbook<::espena::respond_provision_and_amend_rundown> ( &m_pb_respond_provision_and_amend );
  init_playbook<::espena::respond_provision_and_amend_rundown> ( &m_pb_respond_amend               );
  init_playbook<::espena::countdown_rundown>                   ( &m_pb_countdown                   );
  init_playbook<::espena::wifi_rundown>                        ( &m_pb_wifi                        );
  init_playbook<::espena::wifi_provisioning_rundown>           ( &m_pb_wifi_provisioning           );
  init_playbook<::espena::wifi_disconnected_rundown>           ( &m_pb_wifi_disconnected           );
  init_playbook<::espena::wifi_login_rundown>                  ( &m_pb_wifi_login                  );
  init_playbook<::espena::wifi_login_failure_rundown>          ( &m_pb_wifi_login_failure          );
  init_playbook<::espena::wifi_ap_not_found_rundown>           ( &m_pb_wifi_ap_not_found           );
  init_playbook<::espena::main_menu_rundown>                   ( &m_pb_main_menu                   );
  init_playbook<::espena::main_menu_responded_rundown>         ( &m_pb_main_menu_responded         );
  init_playbook<::espena::main_menu_not_sent_rundown>          ( &m_pb_main_menu_not_sent          );
  init_playbook<::espena::mnu_change_response_rundown>         ( &m_pb_mnu_change_response         );
  init_playbook<::espena::venue_rundown>                       ( &m_pb_venue                       );
  init_playbook<::espena::address_rundown>                     ( &m_pb_address                     );
  init_playbook<::espena::time_rundown>                        ( &m_pb_time                        );
  init_playbook<::espena::qrcode_rundown>                      ( &m_pb_qrcode                      );
  init_playbook<::espena::clothing_rundown>                    ( &m_pb_clothing                    );
  init_playbook<::espena::transport_rundown>                   ( &m_pb_transport                   );
  init_playbook<::espena::transport_to_rundown>                ( &m_pb_transport_to                );
  init_playbook<::espena::transport_from_rundown>              ( &m_pb_transport_from              );
  init_playbook<::espena::bring_rundown>                       ( &m_pb_bring                       );
  init_playbook<::espena::wee_rundown>                         ( &m_pb_wee                         );
  init_playbook<::espena::happy_roller_rundown>                ( &m_pb_happy_roller                );
  init_playbook<::espena::neei_rundown>                        ( &m_pb_neei                        );
  init_playbook<::espena::sad_roller_rundown>                  ( &m_pb_sad_roller                  );
  init_playbook<::espena::unable_to_send_rundown>              ( &m_pb_unable_to_send              );
  init_playbook<::espena::website_url_rundown>                 ( &m_pb_website_url                 );
  init_playbook<::espena::sending_to_server_rundown>           ( &m_pb_sending_to_server           );
  init_playbook<::espena::low_battery_rundown>                 ( &m_pb_low_battery                 );
  init_playbook<::espena::nvs_deleted_rundown>                 ( &m_pb_nvs_deleted                 );
} 

void application::restart() {
  run_intro();
}

void application::shutdown() {
  gpio_set_level( GPIO_NUM_33, 1 );
}

void application::app_start() {
  gpio_isr_register( gpio_isr, this, ESP_INTR_FLAG_EDGE, NULL );
  
  RESET_REASON reset_reason_cpu0 = rtc_get_reset_reason( 0 );
  RESET_REASON reset_reason_cpu1 = rtc_get_reset_reason( 1 );

  ESP_LOGI( m_component_name, "CPU0 reset reason: %d", reset_reason_cpu0 );
  ESP_LOGI( m_component_name, "CPU1 reset reason: %d", reset_reason_cpu1 );

  if( reset_reason_cpu0 != POWERON_RESET )
  {
    // Workaround for bug in ESP32 API - brownout resets are not properly flagged.
    // Assume that all unintended resets are due to low voltage.
    ESP_LOGE( m_component_name, "Low battery!" );
    run_playbook( &m_pb_low_battery ); // < will try to continue as usual after warning the user
  }
  else {
    m_cuttable_wire_watcher.start();
    run_intro();
    vTaskDelay( 350 / portTICK_PERIOD_MS );
    m_beeper.beep();
    vTaskDelay( 1000 / portTICK_PERIOD_MS );
    set_button_interrupts();
    vTaskDelay( 500 / portTICK_PERIOD_MS );
  }
}

void application::run() {

  application_task_queue_item item;
  memset( &item, 0x00, sizeof( application_task_queue_item ) );
  item.message = application_task_message::on;
  xQueueSend( m_message_queue, &item, portMAX_DELAY );
  memset( &item, 0x00, sizeof( application_task_queue_item ) );

  size_t free_heap_size = esp_get_free_internal_heap_size();
  size_t min_free_heap_size = esp_get_minimum_free_heap_size();
  ESP_LOGI( m_component_name, "Free heap size: %d, minimum free heap size: %d", free_heap_size, min_free_heap_size );

  while( 1 ) {
    if( xQueueReceive( m_message_queue, &item, 10 ) ) {
      switch( item.message ) {
        case application_task_message::on:
          app_start();
          break;
        case application_task_message::gpio:
          on_gpio();
          break;
        case application_task_message::off:
          gpio_intr_disable( GPIO_NUM_36 );
          ESP_LOGI( m_component_name, "Shutting down..." );
          xQueueReset( m_message_queue );
          m_oled_display.clear();
          vTaskDelay( 250 / portTICK_PERIOD_MS );
          goto terminate;
      }
    }
  }
  terminate:
    shutdown();
    esp_restart(); // To account for unsuccessful power down
}

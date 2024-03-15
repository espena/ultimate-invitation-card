#ifndef __application_hpp__
#define __application_hpp__

#include <driver/gpio.h>
#include <esp_event.h>
#include "freertos/queue.h"
#include "components/captive_portal.hpp"
#include "components/power_timeout.hpp"
#include "components/cuttable_wire_watcher.hpp"
#include "components/playbook_item.hpp"
#include "components/i_playbook.hpp"
#include "components/playbook.hpp"
#include "components/pwm.hpp"
#include "components/time_sync.hpp"
#include "components/tls_connection.hpp"
#include "rundown/i_rundown.hpp"
#include "oled_display.hpp"
#include "font_8x8.hpp"

namespace espena {

  class application {

    /**
      * Reference to the one and only application instance, provided for static methods
      */
    static application *m_the_app;

    /**
      * Message queue
      */
    QueueHandle_t m_message_queue;

    enum class application_task_message {
      on,
      gpio,
      off
    };

    typedef struct application_task_queue_item_struct {
      application_task_message message;
      void *arg;
    } application_task_queue_item;

    // Decision flags
    bool m_did_respond;
    bool m_is_coming;
    bool m_wifi_configured;
    bool m_processing_wire_cut;
    bool m_sending_to_server;
    bool m_wifi_connected;

    /* Used if user changes response */
    cuttable_wire m_changed_wire;

    /* Button indicators */
    components::pwm m_led_btn_a;
    components::pwm m_led_btn_b;
    components::pwm m_led_btn_c;
    components::pwm m_led_btn_d;

    /* Jumper indicators */
    components::pwm m_led_btn_red;
    components::pwm m_led_btn_green;

    /* Beeper */
    components::pwm m_beeper;

    /* NTP time keeper */
    components::time_sync m_time_sync;

    /* TLS connection */
    components::tls_connection m_tls_connection;

    /**
      * Constructor
      * Private to prevent instantiation of more than one instance.
      * Use static get() method to retrieve application instance.
      */
    application();

    ::espena::components::power_timeout m_power_timeout;

    ::espena::components::cuttable_wire_watcher m_cuttable_wire_watcher;

    // Helper function
    void run_playbook( ::espena::i_playbook *playbook );

    // Run startup sequence
    void run_intro();

    // Run main menu sequence
    void run_main_menu();

    // Pointer ot current playbook
    ::espena::i_playbook *m_current_playbook;

    // Startup sequence
    ::espena::components::playbook m_pb_intro;
    
    // Startup sequence if user is coming
    ::espena::components::playbook m_pb_intro_coming;
    
    // Startup sequence if user is not coming
    ::espena::components::playbook m_pb_intro_not_coming;
    
    // Main menu
    ::espena::components::playbook m_pb_main_menu;
    
    // Main menu when responded
    ::espena::components::playbook m_pb_main_menu_responded;
    
    // Main menu when response not yet sent
    ::espena::components::playbook m_pb_main_menu_not_sent;
    
    // Change response menu
    ::espena::components::playbook m_pb_mnu_change_response;
    
    // Information sequence
    ::espena::components::playbook m_pb_info;

    // Information more sequence
    ::espena::components::playbook m_pb_info_more;

    // Respond sequence
    ::espena::components::playbook m_pb_respond;

    // Intro before wifi enabled response
    ::espena::components::playbook m_pb_respond_with_wifi_intro;

    // Respond after WiFi provisioning sequence
    ::espena::components::playbook m_pb_respond_with_wifi;

    // Amend response, re-run WiFi provisioning first
    ::espena::components::playbook m_pb_respond_provision_and_amend;

    // Amend response
    ::espena::components::playbook m_pb_respond_amend;

    // Wire cut countdown
    ::espena::components::playbook m_pb_countdown;

    // Wifi sequence
    ::espena::components::playbook m_pb_wifi;

    // Wifi provisioning sequence
    ::espena::components::playbook m_pb_wifi_provisioning;

    // Wifi disconnct handling sequence
    ::espena::components::playbook m_pb_wifi_disconnected;

    // Wifi logging in sequence
    ::espena::components::playbook m_pb_wifi_login;

    // Wifi login failure sequence
    ::espena::components::playbook m_pb_wifi_login_failure;

    // Wifi AP not found sequence
    ::espena::components::playbook m_pb_wifi_ap_not_found;

    // Time sequence
    ::espena::components::playbook m_pb_time;

    // Venue sequence
    ::espena::components::playbook m_pb_venue;

    // Address sequence
    ::espena::components::playbook m_pb_address;

    // Venue QR code sequence
    ::espena::components::playbook m_pb_qrcode;

    // Clothing sequence
    ::espena::components::playbook m_pb_clothing;

    // Transport sequence
    ::espena::components::playbook m_pb_transport;

    // Transport TO sequence
    ::espena::components::playbook m_pb_transport_to;

    // Transport FROM sequence
    ::espena::components::playbook m_pb_transport_from;

    // Bring-along sequence
    ::espena::components::playbook m_pb_bring;

    // Wire cut green celebration sequence
    ::espena::components::playbook m_pb_wee;

    // Happy message sequence
    ::espena::components::playbook m_pb_happy_roller;

    // Wire cut red catastrophe sequence
    ::espena::components::playbook m_pb_neei;

    // Sad message sequence
    ::espena::components::playbook m_pb_sad_roller;

    // Unable to send request sequence
    ::espena::components::playbook m_pb_unable_to_send;

    // Website URL sequence
    ::espena::components::playbook m_pb_website_url;

    // Sending to server sequence
    ::espena::components::playbook m_pb_sending_to_server;

    // Low battery warning sequence
    ::espena::components::playbook m_pb_low_battery;

    // Non-volatile memory delted message
    ::espena::components::playbook m_pb_nvs_deleted;

    // WiFi captive portal
    ::espena::components::captive_portal m_captive_portal;

    oled_display m_oled_display;
    font_8x8 m_font_8x8;

    void init_button_input( gpio_num_t gpio_num );

    template <typename TRundown>
    void init_playbook( ::espena::components::playbook *pb )
    {
      pb->set_event_loop_handle( m_event_loop_handle );
      pb->add_event_listener( ::espena::components::playbook::event::menu_prompt, event_handler );
      pb->add_event_listener( ::espena::components::playbook::event::cuttable_wire, event_handler );
      pb->add_event_listener( ::espena::components::playbook::event::beep, event_handler );
      pb->add_event_listener( ::espena::components::playbook::event::menu_select, event_handler );
      pb->add_event_listener( ::espena::components::playbook::event::play_finished, event_handler );
      TRundown::load( pb );
    };
    
    void set_button_interrupts();

    void init_inputs();

    void init_playbooks();

    void erase_none_volatile_storage();

    void app_start();

    void event_handler_playbook( ::espena::components::playbook::event event_id, void *event_params );
    void event_handler_cuttable_wire( ::espena::components::cuttable_wire_watcher::event event_id, espena::cuttable_wire wire );
    void event_handler_power_timeout( ::espena::components::power_timeout::event event_id );
    void event_handler_captive_portal_wifi( ::espena::components::captive_portal_wifi::event event_id );

    void change_response( cuttable_wire wire );
    void transmit_to_server( cuttable_wire wire );

    void on_menu_prompt( ::espena::playbook_item *playbook_item );
    void on_menu_select( ::espena::menu_select menu_selection );

    void on_cuttable_wire( ::espena::cuttable_wire wire );

    void on_playbook_finished( ::espena::components::playbook *playbook );
    void on_playbook_reset( ::espena::components::playbook *playbook );

    void set_wifi_status( bool is_connected );

    bool test_network_connection();
  
    void set_nvs_respond_flags( espena::cuttable_wire wire );

    bool send_response_to_server( ::espena::cuttable_wire wire );
    
    void wait_for_flag( bool &flag, uint32_t timeout_ms );

    public:

      const static char m_component_name[];

      /**
       * Get the one and only application instance
       */
      static application *get();

      /**
       * Handle to custom event loop
       */
      esp_event_loop_handle_t m_event_loop_handle;

      /**
        * Event - static handler for all incoming events
        */
      static void event_handler( void *handler_arg,
                                 esp_event_base_t event_base,
                                 int32_t event_id,
                                 void *event_params );

      /**
       * GPIO ISR
       */
      static void gpio_isr( void *arg );

      void on_gpio();

      /**
       * Program start
       */
      void run();
      
      /**
       * Restart
       */
      void restart();

      /**
       * Power off
       */
      void shutdown();

  }; // class application

}; // namespace espena

#endif // __application_hpp__

idf_component_register( SRCS "main.cpp"
                             "application.cpp"
                             "pwm_audio.c"
                             "components/captive_portal.cpp"
                             "components/captive_portal_wifi.cpp"
                             "components/captive_portal_dns.cpp"
                             "components/captive_portal_http.cpp"
                             "components/event/event_dispatcher.cpp"
                             "components/playbook.cpp"
                             "components/oled_display.cpp"
                             "components/cuttable_wire_watcher.cpp"
                             "components/power_timeout.cpp"
                             "components/pwm.cpp"
                             "components/time_sync.cpp"
                             "components/tls_connection.cpp"
                             "resources/font_8x8.cpp"
                             "rundown/intro_rundown.cpp"
                             "rundown/intro_coming_rundown.cpp"
                             "rundown/intro_not_coming_rundown.cpp"
                             "rundown/main_menu_rundown.cpp"
                             "rundown/main_menu_not_sent_rundown.cpp"
                             "rundown/main_menu_responded_rundown.cpp"
                             "rundown/mnu_change_response_rundown.cpp"
                             "rundown/info_rundown.cpp"
                             "rundown/info_more_rundown.cpp"
                             "rundown/time_rundown.cpp"
                             "rundown/venue_rundown.cpp"
                             "rundown/qrcode_rundown.cpp"
                             "rundown/address_rundown.cpp"
                             "rundown/clothing_rundown.cpp"
                             "rundown/transport_rundown.cpp"
                             "rundown/transport_to_rundown.cpp"
                             "rundown/transport_from_rundown.cpp"
                             "rundown/bring_rundown.cpp"
                             "rundown/respond_rundown.cpp"
                             "rundown/respond_with_wifi_intro_rundown.cpp"
                             "rundown/respond_with_wifi_rundown.cpp"
                             "rundown/respond_provision_and_amend_rundown.cpp"
                             "rundown/respond_rundown.cpp"
                             "rundown/countdown_rundown.cpp"
                             "rundown/wifi_rundown.cpp"
                             "rundown/wifi_provisioning_rundown.cpp"
                             "rundown/wifi_disconnected_rundown.cpp"
                             "rundown/wifi_login_rundown.cpp"
                             "rundown/wifi_login_failure_rundown.cpp"
                             "rundown/wifi_ap_not_found_rundown.cpp"
                             "rundown/wee_rundown.cpp"
                             "rundown/happy_roller_rundown.cpp"
                             "rundown/neei_rundown.cpp"
                             "rundown/sad_roller_rundown.cpp"
                             "rundown/unable_to_send_rundown.cpp"
                             "rundown/website_url_rundown.cpp"
                             "rundown/sending_to_server_rundown.cpp"
                             "rundown/low_battery_rundown.cpp"
                             "rundown/nvs_deleted_rundown.cpp"
               INCLUDE_DIRS  "./resources"
                             "./components"
              EMBED_TXTFILES "resources/isrgrootx1.pem" )
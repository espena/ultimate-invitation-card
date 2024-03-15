#ifndef __PLAYBOOK_ITEM_HPP__
#define __PLAYBOOK_ITEM_HPP__

#include <stdint.h>

namespace espena {

  enum menu_key {
    A = 0,
    B = 1,
    C = 2,
    D = 3,
    NONE = -1
  };

  enum class cuttable_wire {
    none  = 0x00u,
    red   = 0x01u,
    green = 0x02u,
    all  =  0xFFu
  };

  inline cuttable_wire operator | ( cuttable_wire a, cuttable_wire b ) {
    return static_cast<cuttable_wire>( static_cast<uint8_t>( a ) | static_cast<uint8_t>( b ) );
  }

  inline cuttable_wire operator & ( cuttable_wire a, cuttable_wire b ) {
    return static_cast<cuttable_wire>( static_cast<uint8_t>( a ) & static_cast<uint8_t>( b ) );
  }

  enum class menu_select {
    none = 0x00,
    main,
    info,
    info_more,
    time,
    address,
    directions,
    clothing,
    transport,
    sleepover,
    transport_to,
    transport_from,
    bring,
    website_url,
    wifi_use_mobile,
    wifi_provisioning,
    map,
    venue,
    ready_to_respond,
    respond,
    change_response,
    change_to_not_coming,
    change_to_is_coming,
    send_response,
    wee,
    help,
    restart,
    countdown,
    shutdown
  };

  enum class playbook_item_type {
    text,
    roll,
    menu,
    image,
    await,
    transition
  };

  typedef struct que_point_struct {
    unsigned int line_number_in;
    unsigned int line_number_out;
    cuttable_wire wire;
  } que_point;

  typedef struct playbook_item_struct {
    playbook_item_type type;
    const uint8_t *buf;
    struct {
      menu_select event[ 4 ];
      int beep;
      int delay_ms;
      int line_count;
      que_point que_points[ 4 ];
      struct {
        int frame_begin;
        int frame_end;
        int delay_ms;
        int param;
      } tween;
    } params;
  } playbook_item;

}

#endif // __PLAYBOOK_ITEM_HPP__
/**
  ÆØÅ æøå This source file MUST be encoded as ISO8859-1 (Latin1)
*/

#ifndef ISO8859_1_TEXT_H
#define ISO8859_1_TEXT_H
#include "../p13n.hpp"

typedef enum {
  txt_invitation         =  0,
  txt_accompany          =  1,
  mnu_main               =  2,
  mnu_main_responded     =  3,
  mnu_main_not_sent      =  4,
  mnu_info               =  5,
  mnu_change_response    =  6,
  txt_respond1           =  7,
  txt_respond2           =  8,
  txt_respond3           =  9,
  mnu_info_more          = 10,
  mnu_venue              = 11,
  mnu_reply              = 12,
  txt_qrcode_advice      = 13,
  txt_time               = 14,
  mnu_time               = 15,
  txt_address            = 16,
  txt_clothing1          = 17,
  txt_clothing2          = 18,
  txt_clothing3          = 19,
  txt_clothing4          = 20,
  txt_clothing5          = 21,
  txt_transport1         = 22,
  txt_bring1             = 23,
  txt_bring2             = 24,
  txt_bring3             = 25,
  txt_wifi1              = 26,
  txt_wifi2              = 27,
  txt_wifi3              = 28,
  txt_wifi4              = 29,
  txt_wifi5              = 30,
  txt_wifi6              = 31,
  txt_wifi7              = 32,
  txt_wifi8              = 33,
  txt_wifi9              = 34,
  txt_wifi10             = 35,
  txt_wifi11             = 36,
  txt_wifi12             = 37,
  txt_pliers             = 38,
  txt_wirecut1           = 39,
  txt_wirecut2           = 40,
  txt_wirecut3           = 41,
  txt_wirecut4           = 42,
  txt_wirecut5           = 43,
  txt_ready_or_not       = 44,
  txt_transport_to_start = 45,
  txt_transport_to_menu  = 46,
  txt_transport_fr_start = 47,
  txt_transport_fr_menu  = 48,
  txt_sending_to_server  = 49,
  txt_invit_acc_start    = 50,
  txt_invit_acc_menu     = 51,
  txt_invit_reject_start = 52,
  txt_invit_alter_resp   = 53,
  txt_invit_sending      = 54,
  txt_invit_send_err     = 55,
  txt_invit_send_retry   = 56,
  txt_invit_reject_menu  = 57,
  txt_low_battery        = 58,
  txt_nvs_deleted        = 59,
  txt_support            = 60,
  txt_p13n_greeting      = 61
} iso8859_1_text_id;

const uint8_t iso8859_1_text[ ][ 8 ][ 17 ] = {
  { // txt_invitation
    "                ",
    "   INVITASJON   ",
    "   ``````````   ",
    "   Du/dere er   ",
    "  ønsket på en  ",
    "  etterlengtet  ",
    "   nerde-fest   ",
    "                "
  },
  { // txt_accompany
    "                ",
    "   INVITASJON   ",
    "   ``````````   ",
    "   Kom gjerne   ",
    "   med følge!   ",
    "                ",
    "                ",
    "                "
},
{ // mnu_main
    "                ",
    " BRUK KNAPPENE  ",
    " `````````````` ",
    " [A] Festinfo   ",
    " [B] Svar her   ",
    "                ",
    " [D] Avslutt    ",
    "                "
  },
  { // mnu_main_responded
    "                ",
    " BRUK KNAPPENE  ",
    " `````````````` ",
    " [A] Festinfo   ",
    " [B] Endre svar ",
    " [C] Nettside   ",
    " [D] Avslutt    ",
    "                "
  },
  { // mnu_main_not_sent
    "                ",
    " BRUK KNAPPENE  ",
    " `````````````` ",
    " [A] Festinfo   ",
    " [B] Endre svar ",
    " [C] Sende svar ",
    " [D] Avslutt    ",
    "                "
  },
  { // mnu_info
    "                ",
    " INFO           ",
    " `````````````` ",
    " [A] Tid        ",
    " [B] Sted       ",
    " [C] Mer info   ",
    " [D] <Tilbake   ",
    "                "
  },
  { // mnu_change_response
    "                ",
    " KOMMER DU?     ",
    " ``````````     ",
    " [A] JA!        ",
    " [B] NEI!       ",
    "                ",
    " [D] <Tilbake   ",
    "                "
  },
  { // txt_respond1
    "                ",
    " KLARGJØRING    ",
    " ```````````    ",
    " Konfigurerer   ",
    " WiFi...        ",
    "                ",
    "                ",
    "                "
  },
  { // txt_respond2
    "                ",
    " FIKSE WIFI?    ",
    " `````````````` ",
    " [A] Kjør på!   ",
    "                ",
    "                ",
    " [D] <Tilbake   ",
    "                "
  },
  { // txt_respond3
    "                ",
    " SVAR           ",
    " `````````````` ",
    " [A] Gi svar    ",
    " [B] WiFi       ",
    "                ",
    " [D] <Tilbake   ",
    "                "
  },
  { // mnu_info_more
    "                ",
    " OPPLEGG        ",
    " `````````````` ",
    " [A] Antrekk    ",
    " [B] Ta med...  ",
    " [C] Transport  ",
    " [D] <Tilbake   ",
    "                "
  },
  { // mnu_venue
    "                ",
    " STED           ",
    " `````````````` ",
    " [A] Adresse    ",
    " [B] QR Kart    ",
    "                ",
    " [D] <Tilbake   ",
    "                "
  },
  { // mnu_reply
    "                ",
    " SVAR           ",
    " `````````````` ",
    " [A] Gi svar    ",
    "                ",
    "                ",
    " [D] <Tilbake   ",
    "                "
  },
  { // txt_qrcode_advice
    "                ",
    "    QR-kode     ",
    "   funker kun   ",
    "   av og til!   ",
    "   Bruk makro   ",
    "    og zoom!    ",
    "                ",
    "                "
  },
  { // txt_time
    "                ",
    "     LØRDAG     ",
    "                ",
    "    29. JUNI    ",
    "    ````````    ",
    "  ÅPEN DØR FRA  ",
    "    KL 16:00    ",
    "       `````    "
  },
  { // mnu_time
    "                ",
    "  Det blir mat  ",
    "                ",
    "    kl 18:00    ",
    "       `````    ",
    "                ",
    " [D] <Tilbake   ",
    "                "
  },
  { // txt_address
    "                ",
    " ADRESSE        ",
    " `````````````` ",
    "                ",
    "                ",
    "                ",
    " [D] <Tilbake   ",
    "                "
  },
  { // txt_clothing1
    "                ",
    " ANTREKK        ",
    " `````````````` ",
    " CASUAL         ",
    "                ",
    "                ",
    "                ",
    "                "
  },
  { // txt_clothing2
    "                ",
    " ANTREKK        ",
    " `````````````` ",
    " SKIUALEST      ",
    "                ",
    "                ",
    "                ",
    "                "
  },
  { // txt_clothing3  
    "                ",
    " ANTREKK        ",
    " `````````````` ",
    " SKI NL ST      ",
    "                ",
    "                ",
    "                ",
    "                "
  },
  { // txt_clothing4
    "                ",
    " ANTREKK        ",
    " `````````````` ",
    " SKINNVEST      ",
    "                ",
    "                ",
    "                ",
    "                "
  },
  { // txt_clothing5
    "                ",
    " ANTREKK        ",
    " `````````````` ",
    " CASUAL         ",
    "                ",
    "                ",
    " [D] <Tilbake   ",
    "                "
  },
  { // txt_transport1
    "                ",
    " Transport      ",
    " `````````````` ",
    " [A] Til        ",
    " [B] Fra        ",
    "                ",
    " [D] <Tilbake   ",
    "                "
  },
  { // txt_bring1
    "                ",
    " TA MED         ",
    " `````````````` ",
    "   Godt humør   ",
    "    og noe å    ",
    "   helle i deg  ",
    "                ",
    "                "
  },
  { // txt_bring2
    "                ",
    " TA MED         ",
    " `````````````` ",
    " Espen stiller  ",
    " med mat og en  ",
    "  del drikke    ",
    "                ",
    "                "
  },
  { // txt_bring3
    "                ",
    " TA MED         ",
    " `````````````` ",
    "  Meny kommer   ",
    "  litt senere   ",
    "                ",
    " [D] <Tilbake   ",
    "                "
  },
  { // txt_wifi1
    "                ",
    " WIFI-OPPSETT   ",
    " `````````````` ",
    " Du trenger PC  ",
    " eller telefon  ",
    "                ",
    " [A] Klar!      ",
    "                "
  },
  { // txt_wifi2
    "                ",
    " WIFI-OPPSETT   ",
    " `````````````` ",
    " [A] Start      ",
    "                ",
    "                ",
    " [D] Avbryt     ",
    "                "
  },
  { // txt_wifi3
    "                ",
    " WIFI-OPPSETT   ",
    " `````````````` ",
    " Oppretter      ",
    " midlertidig    ",
    " WiFi-nettverk  ",
    "                ",
    "                "
  },
  { // txt_wifi4
    "                ",
    " WIFI-OPPSETT   ",
    " `````````````` ",
    "                ",
    "      OK!       ",
    "                ",
    "                ",
    "                "
  },
  { // txt_wifi5
    "                ",
    " WIFI-OPPSETT   ",
    " `````````````` ",
    " Shit!          ",
    " Noe gikk gæli  ",
    "                ",
    " [A] Tilbake    ",
    "                "
  },
  { // txt_wifi6
    "                ",
    " WIFI-OPPSETT   ",
    " `````````````` ",
    " Fra PC/mobil,  ",
    " koble til WiFi ",
    "                ",
      P13N_SSID_OLED  ,
    "                "
  },
  { // txt_wifi7
    "                ",
    " WIFI-OPPSETT   ",
    " `````````````` ",
    " Tilkobling OK! ",
    "                ",
    " Følg veiledn.  ",
    " som kommer opp ",
    "                "
  },
  { // txt_wifi8
    "                ",
    " Om siden ikke  ",
    " vises, gå til  ",
    "                ",
    "                ",
    " ```````````    ",
    " [D] Avbryt     ",
    "                "
  },
  { // txt_wifi9
    "                ",
    " WIFI FRAKOBLET ",
    " `````````````` ",
    " [A] Koble til  ",
    "                ",
    "                ",
    " [D] Avbryt     ",
    "                "
  },
  { // txt_wifi10
    "                ",
    " WIFI-OPPSETT   ",
    " `````````````` ",
    " Logger på...   ",
    "                ",
    "                ",
    " [D] Avbryt     ",
    "                "
  },
  { // txt_wifi11
    "                ",
    " WIFI-OPPSETT   ",
    " `````````````` ",
    " Feil passord,  ",
    " prøv igjen!    ",
    "                ",
    " [D] <Tilbake   ",
    "                "
  },
  { // txt_wifi12
    "                ",
    " WIFI-OPPSETT   ",
    " `````````````` ",
    " Nettverk ikke  ",
    " funnet!        ",
    "                ",
    " [D] <Tilbake   ",
    "                "
  },
  { // txt_pliers
    "                ",
    " NB !!          ",
    " `````````````` ",
    " Du må ha en    ",
    "                ",
    " AVBITERTANG!   ",
    "                ",
    "                "
  },
  { // wire cut 1
    "                ",
    " This your      ",
    " last chance.   ",
    "                ",
    " After this     ",
    " there is no    ",
    " turning back.  ",
    "                "
  },
  { // wire cut 2
    " You cut the    ",
    " RED wire, the  ",
    " story ends.    ",
    "                ",
    " You wake up in ",
    " your bed and   ",
    " believe what-  ",
    " ever you want. "
  },
  { // wire cut 3
    " You cut the    ",
    " GREEN wire,    ",
    " you stay in    ",
    " wonderland,    ",
    " and I show you ",
    " how deep the   ",
    " rabbit hole    ",
    " goes.          "
  },
  { // wire cut 4
    "                ",
    " Remenber, all  ",
    " I'm offering   ",
    " is a party.    ",
    "                ",
    "                ",
    " Nothing more.  ",
    "                "
  },
  { // wire cut 5
    "                ",
    " KLIPP LEDNING? ",
    " `````````````` ",
    " [A] YESS!      ",
    "                ",
    "                ",
    " [D] Tør ikke   ",
    "                "
  },
  { // ready or not
    "                ",
    " KLAR!          ",
    " `````````````` ",
    " [A] Fortsett   ",
    "                ",
    "                ",
    " [D] Avbryt     ",
    "                "
  },
  { // transport TO start
    "                ",
    " Det er lett    ",
    " å komme seg    ",
    " hit med enten  ",
    " buss eller     ",
    " bil.           ",
    "                ",
    "                ",
  },
  { // transport TO menu
    " Gå av på       ",
    " Høyenhall rett ",
    " etter Steins-  ",
    " åsen.          ",
    "                ",
    " [A] Gjenta     ",
    "                ",
    " [D] <Tilbake   "
  },
  { // transport FROM start
    "                ",
    " Jeg tar sikte  ",
    " på å forhånds- ",
    " bestille taxi  ",
    " etter behov    ",
    " rundt midnatt. ",
    "                ",
    "                "
  },
  { // transport FROM menu
    " Rute 200 har   ",
    " siste avgang   ",
    " mot Oslo rundt ",
    " kl 22:00.      ",
    "                ",
    " [A] Gjenta     ",
    "                ",
    " [D] <Tilbake   "
  },
  { // sending to server...
    "                ",
    " SENDER SVAR    ",
    " ```````````    ",
    " Vent mens jeg  ",
    " sender svaret  ",
    " til server...  ",
    "                ",
    "                ",
  },
  { // invitation accept start
    "                ",
    " VELKOMMEN!     ",
    " ``````````     ",
    " Takk for at du ",
    " vil være med!  ",
    "                ",
    "                ",
    "                ",
  },
  { // invitation accept menu
    "                ",
    "                ",
    "                ",
      P13N_WWW_CODE   ,
    "                ",
    "                ",
    " [D] <Tilbake   ",
    "                "
  },
  { // invitation rejected start
    "                ",
    " DÆNG!          ",
    " `````          ",
    " Synd du ikke   ",
    " får vært med!  ",
    "                ",
    "                ",
    "                "
  },
  { // invitation alter response
    "                ",
    " DÆNG!          ",
    " `````          ",
    " Du kan endre   ",
    " svaret fra     ",
    " neste meny     ",
    "                ",
    "                "
  },
  { // invitation sending to server
    "                ",
    " VENT LITT      ",
    " `````````      ",
    " Sender svar    ",
    " til server...  ",
    "                ",
    "                ",
    "                "
  },
  { // unable to send
    "                ",
    "  SENDINGSFEIL  ",
    "  ````````````  ",
    "   Kunne ikke   ",
    "   sende svar   ",
    "   til server   ",
    "                ",
    "                "
  },
  { // retry sending response
    "                ",
    "  SENDINGSFEIL  ",
    "  ````````````  ",
    " For å prøve på ",
    "   nytt, velg   ",
    "  'Sende svar'  ",
    " fra neste meny ",
    "                "
  },
  { // invitation rejected menu
    "                ",
    "                ",
    "                ",
      P13N_WWW_CODE   ,
    "                ",
    "                ",
    " [D] <Tilbake   ",
    "                "
  },
  { // low battery warning
    "                ",
    " LAVT BATTERI   ",
    " ````````````   ",
    " Skru ut kortet ",
    " og sett i nye  ",
    " AAA-batterier, ",
    " helst lithium! ",
    "                "
  },
  { // deleting NVRAM
    "                ",
    " SLETTER NVS    ",
    " ```````````    ",
    " Nullstiller    ",
    " persistente    ",
    " datalagre      ",
    "                ",
    "                "
  },
  { // support
    "                ",
    "                ",
    "    Support:    ",
    "                ",
    "                ",
    "                ",
    "                ",
    "                "
  },  
  /* PERSONALIZATIONS */
  //txt_p13n_greeting
#if defined(P13N_PER)
  {
    "                ",
    "   INVITASJON   ",
    "   ``````````   ",
    "     Kjære      ",
    "      Per       ",
    "                ",
    "                ",
    "                "
  }
#endif
  };

#endif // ISO8859_1_TEXT_H
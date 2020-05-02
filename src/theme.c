#include "theme.h"

#include "debug.h"
#include "filesys.h"
#include "theme_tables.h"
#include "ui.h"

#include <stdlib.h>
#include <string.h>

#define COLOR_PROC(a_ulColor) RGB((a_ulColor >> 16) & 0x0000FF, (a_ulColor >> 8) & 0x0000FF, a_ulColor & 0x0000FF)

/* Solarized color scheme */
#define SOLAR_BASE03 0x002b36
#define SOLAR_BASE02 0x073642
#define SOLAR_BASE01 0x586e75
#define SOLAR_BASE00 0x657b83
#define SOLAR_BASE0 0x839496
#define SOLAR_BASE1 0x93a1a1
#define SOLAR_BASE2 0xeee8d5
#define SOLAR_BASE3 0xfdf6e3
#define SOLAR_YELLOW 0xb58900
#define SOLAR_ORANGE 0xcb4b16
#define SOLAR_RED 0xdc322f
#define SOLAR_MAGENTA 0xd33682
#define SOLAR_VIOLET 0x6c71c4
#define SOLAR_BLUE 0x268bd2
#define SOLAR_CYAN 0x2aa198
#define SOLAR_GREEN 0x859900

/* Monokai color scheme */
#define MONOKAI_BROWN0 0x1A1B15
#define MONOKAI_BROWN1 0x282923
#define MONOKAI_BROWN2 0x383830
#define MONOKAI_BROWN3 0x3A392F
#define MONOKAI_GRAY1 0x787975
#define MONOKAI_GRAY2 0x90918B
#define MONOKAI_GRAY3 0xD3D3D2
#define MONOKAI_GRAY4 0x383934
#define MONOKAI_GRAY5 0x555652
#define MONOKAI_WHITE 0xDADAD4
#define MONOKAI_ORANGE1 0x51391B
#define MONOKAI_ORANGE2 0xA45600
#define MONOKAI_ORANGE3 0xEC8319
#define MONOKAI_STATUS_GREEN 0x159F49
#define MONOKAI_STATUS_YELLOW 0xAFA123
#define MONOKAI_STATUS_RED 0xDF4249

/* Reaper color scheme */
#define REAPER_GRAY0 0x2B2B2B
#define REAPER_GRAY1 0x333333
#define REAPER_GRAY2 0x454545
#define REAPER_GRAY3 0x424242
#define REAPER_GRAY4 0x595959
#define REAPER_GRAY5 0x5C5C5C
#define REAPER_GRAY6 0x747474
#define REAPER_GRAY7 0x939393
#define REAPER_GREEN1 0x2D4F47
#define REAPER_GREEN2 0x339887
#define REAPER_GREEN3 0x12BC98
#define REAPER_GREEN4 0x35CEB5
#define REAPER_STATUS_GREEN 0x00FE95
#define REAPER_STATUS_RED 0xBB2500
#define REAPER_STATUS_YELLOW 0xBFBF00

/* Atom color scheme */
#define ATOM_GRAYBLUE0 0x181A1F
#define ATOM_GRAYBLUE1 0x21252B
#define ATOM_GRAYBLUE2 0x252830
#define ATOM_GRAYBLUE3 0x282C34
#define ATOM_GRAYBLUE4 0x3E4451
#define ATOM_GRAYBLUE5 0x353940
#define ATOM_GRAYBLUE6 0x40444D
#define ATOM_GRAYBLUE7 0x3B4048
#define ATOM_GRAYBLUE8 0x4B5364
#define ATOM_GRAYBLUE9 0xABB2BF
#define ATOM_BLUE 0x568AF2
#define ATOM_STATUS_RED 0xBB263A
#define ATOM_STATUS_GREEN 0x76BB26 // not used
#define ATOM_STATUS_YELLOW 0xBBAF26

/* Mojave dark color scheme */
#define MOJAVE_GRAY1 0x232227
#define MOJAVE_GRAY2 0x37363B
#define MOJAVE_GRAY3 0xDEDFE1
#define MOJAVE_GRAY4 0x535458
#define MOJAVE_GRAY5 0x4F5055
#define MOJAVE_GRAY6 0x6A696E
#define MOJAVE_GRAY7 0xC6C7CB
#define MOJAVE_GRAY8 0x424146
#define MOJAVE_STATUS_RED 0xFE5C52
#define MOJAVE_STATUS_GREEN 0x46C130
#define MOJAVE_STATUS_YELLOW 0xE5BF2B

/* Calypso color scheme */
#define CALYPSO_GRAY1 0x776148
#define CALYPSO_GRAY2 0x202124
#define CALYPSO_GRAY3 0x202124
#define CALYPSO_GRAY4 0x454750
#define CALYPSO_GRAY5 0x141720
#define CALYPSO_GRAY6 0x585B62
#define CALYPSO_GRAY7 0x424449
#define CALYPSO_GRAY8 0x5B5E65
#define CALYPSO_RED 0xDF4249
#define CALYPSO_GREEN 0x159F49
#define CALYPSO_YELLOW 0xAFA123

/* Focal Fossa Dark color scheme */
#define FOSSA_CONSOLE_BG_PURPLE 0x300A24
#define FOSSA_DARK_TEXT 0x9D9E9B
#define FOSSA_LIGHT_TEXT 0xFFFFFF
#define FOSSA_SPOTLIGHT_TEXT 0xDF4A16
#define FOSSA_DARK_ORANGE 0xE94915
#define FOSSA_LIGHT_ORANGE 0xDF4A16
#define FOSSA_DARK_PURPLE 0x783F72
#define FOSSA_LIGHT_PURPLE 0x956490
#define FOSSA_DARKEST_GRAY 0x343434
#define FOSSA_DARK_GRAY 0x3A3A3A
#define FOSSA_MID_GRAY 0x3E3E3E
#define FOSSA_LIGHT_GRAY 0x484848
#define FOSSA_LIGHTEST_GRAY 0x585858
#define FOSSA_STATUS_RED 0x000000
#define FOSSA_STATUS_GREEN 0x000000
#define FOSSA_STATUS_YELLOW 0x000000


uint32_t COLOR_BKGRND_MAIN;
uint32_t COLOR_BKGRND_ALT;
uint32_t COLOR_BKGRND_AUX;
uint32_t COLOR_BKGRND_MENU;
uint32_t COLOR_BKGRND_MENU_HOVER;
uint32_t COLOR_BKGRND_MENU_ACTIVE;
uint32_t COLOR_BKGRND_LIST;
uint32_t COLOR_BKGRND_LIST_HOVER;

uint32_t COLOR_MAIN_TEXT;
uint32_t COLOR_MAIN_TEXT_CHAT;
uint32_t COLOR_MAIN_TEXT_SUBTEXT;
uint32_t COLOR_MAIN_TEXT_ACTION;
uint32_t COLOR_MAIN_TEXT_QUOTE;
uint32_t COLOR_MAIN_TEXT_RED;
uint32_t COLOR_MAIN_TEXT_URL;
uint32_t COLOR_MAIN_TEXT_HINT;

uint32_t COLOR_MSG_USER;
uint32_t COLOR_MSG_USER_PEND;
uint32_t COLOR_MSG_USER_ERROR;
uint32_t COLOR_MSG_CONTACT;

uint32_t COLOR_MENU_TEXT;
uint32_t COLOR_MENU_TEXT_SUBTEXT;
uint32_t COLOR_MENU_TEXT_ACTIVE;

uint32_t COLOR_LIST_TEXT;
uint32_t COLOR_LIST_TEXT_SUBTEXT;

uint32_t COLOR_AUX_EDGE_NORMAL;
uint32_t COLOR_AUX_EDGE_HOVER;
uint32_t COLOR_AUX_EDGE_ACTIVE;
uint32_t COLOR_AUX_TEXT;
uint32_t COLOR_AUX_ACTIVEOPTION_BKGRND;
uint32_t COLOR_AUX_ACTIVEOPTION_TEXT;

uint32_t COLOR_GROUP_SELF;
uint32_t COLOR_GROUP_PEER;
uint32_t COLOR_GROUP_AUDIO;
uint32_t COLOR_GROUP_MUTED;

uint32_t COLOR_SELECTION_BACKGROUND;
uint32_t COLOR_SELECTION_TEXT;

uint32_t COLOR_EDGE_NORMAL;
uint32_t COLOR_EDGE_ACTIVE;
uint32_t COLOR_EDGE_HOVER;

uint32_t COLOR_ACTIVEOPTION_BKGRND;
uint32_t COLOR_ACTIVEOPTION_TEXT;

uint32_t COLOR_STATUS_ONLINE;
uint32_t COLOR_STATUS_AWAY;

uint32_t COLOR_STATUS_BUSY;
uint32_t COLOR_BTN_SUCCESS_BKGRND;
uint32_t COLOR_BTN_SUCCESS_TEXT;
uint32_t COLOR_BTN_SUCCESS_BKGRND_HOVER;
uint32_t COLOR_BTN_SUCCESS_TEXT_HOVER;

uint32_t COLOR_BTN_WARNING_BKGRND;
uint32_t COLOR_BTN_WARNING_TEXT;
uint32_t COLOR_BTN_WARNING_BKGRND_HOVER;
uint32_t COLOR_BTN_WARNING_TEXT_HOVER;

uint32_t COLOR_BTN_DANGER_BACKGROUND;
uint32_t COLOR_BTN_DANGER_TEXT;
uint32_t COLOR_BTN_DANGER_BKGRND_HOVER;
uint32_t COLOR_BTN_DANGER_TEXT_HOVER;

uint32_t COLOR_BTN_DISABLED_BKGRND;
uint32_t COLOR_BTN_DISABLED_TEXT;
uint32_t COLOR_BTN_DISABLED_BKGRND_HOVER;
uint32_t COLOR_BTN_DISABLED_TRANSFER;

uint32_t COLOR_BTN_INPROGRESS_BKGRND;
uint32_t COLOR_BTN_INPROGRESS_TEXT;
uint32_t COLOR_BTN_DISABLED_FORGRND;
uint32_t COLOR_BTN_INPROGRESS_FORGRND;

uint32_t status_color[4];

/**
 * Loads a custom theme and sets out to the size of the data
 *
 * Returns a pointer to the theme data on success, the caller needs to free this
 * Returns NULL on failure
 */
static uint8_t *utox_data_load_custom_theme(size_t *out);
static void read_custom_theme(const uint8_t *data, size_t length);
static uint32_t try_parse_hex_colour(char *color, bool *error);

void theme_load(const THEME loadtheme) {
    // Update the settings dropdown UI

    // ==== Default theme     ====
    // ---- Background Colors ----
    COLOR_BKGRND_MAIN        = COLOR_PROC(0xffffff);
    COLOR_BKGRND_ALT         = COLOR_PROC(0xaaaaaa);
    COLOR_BKGRND_AUX         = COLOR_PROC(0x313131);
    COLOR_BKGRND_LIST        = COLOR_PROC(0x414141);
    COLOR_BKGRND_LIST_HOVER  = COLOR_PROC(0x505050);
    COLOR_BKGRND_MENU        = COLOR_PROC(0x1c1c1c);
    COLOR_BKGRND_MENU_HOVER  = COLOR_PROC(0x282828);
    COLOR_BKGRND_MENU_ACTIVE = COLOR_PROC(0x414141);

    /* ---- Text Colors --- */
    COLOR_MAIN_TEXT         = COLOR_PROC(0x333333);
    COLOR_MAIN_TEXT_CHAT    = COLOR_PROC(0x000000);
    COLOR_MAIN_TEXT_SUBTEXT = COLOR_PROC(0x414141);
    COLOR_MAIN_TEXT_ACTION  = COLOR_PROC(0x4e4ec8);
    COLOR_MAIN_TEXT_QUOTE   = COLOR_PROC(0x008000);
    COLOR_MAIN_TEXT_RED     = COLOR_PROC(0xFF0000);
    COLOR_MAIN_TEXT_URL     = COLOR_PROC(0x001fff);
    COLOR_MAIN_TEXT_HINT    = COLOR_PROC(0x969696);

    /* Message window colors */
    COLOR_MSG_USER       = COLOR_MAIN_TEXT_SUBTEXT;
    COLOR_MSG_USER_PEND  = COLOR_MAIN_TEXT_ACTION;
    COLOR_MSG_USER_ERROR = COLOR_MAIN_TEXT_RED;
    COLOR_MSG_CONTACT    = COLOR_MAIN_TEXT;

    //---- Friend list header and bottom-left buttons ----
    COLOR_MENU_TEXT         = COLOR_BKGRND_MAIN;
    COLOR_MENU_TEXT_SUBTEXT = COLOR_PROC(0xd1d1d1);
    COLOR_MENU_TEXT_ACTIVE  = COLOR_BKGRND_MAIN;

    //---- Friend list  ----
    COLOR_LIST_TEXT         = COLOR_MENU_TEXT;
    COLOR_LIST_TEXT_SUBTEXT = COLOR_MENU_TEXT_SUBTEXT;

    //---- Groupchat user list and title ----
    COLOR_GROUP_SELF  = COLOR_PROC(0x6bc260);
    COLOR_GROUP_PEER  = COLOR_MAIN_TEXT_HINT;
    COLOR_GROUP_AUDIO = COLOR_PROC(0xc84e4e);
    COLOR_GROUP_MUTED = COLOR_MAIN_TEXT_ACTION;

    //---- Text selection ----
    COLOR_SELECTION_BACKGROUND = COLOR_MAIN_TEXT;
    COLOR_SELECTION_TEXT       = COLOR_BKGRND_MAIN;

    //---- Inputs, dropdowns & tooltips ----
    COLOR_EDGE_NORMAL         = COLOR_PROC(0xc0c0c0);
    COLOR_EDGE_HOVER          = COLOR_PROC(0x969696);
    COLOR_EDGE_ACTIVE         = COLOR_PROC(0x4ea6ea);
    COLOR_ACTIVEOPTION_BKGRND = COLOR_PROC(0xd1d1d1);
    COLOR_ACTIVEOPTION_TEXT   = COLOR_MAIN_TEXT;

    //---- Auxiliary style for inputs/dropdowns ("Search friends" bar) ----
    COLOR_AUX_EDGE_NORMAL         = COLOR_BKGRND_AUX;
    COLOR_AUX_EDGE_HOVER          = COLOR_PROC(0x999999);
    COLOR_AUX_EDGE_ACTIVE         = COLOR_PROC(0x1A73B7);
    COLOR_AUX_TEXT                = COLOR_LIST_TEXT;
    COLOR_AUX_ACTIVEOPTION_BKGRND = COLOR_BKGRND_LIST_HOVER;
    COLOR_AUX_ACTIVEOPTION_TEXT   = COLOR_AUX_TEXT;

    //---- Status circles ----
    COLOR_STATUS_ONLINE = COLOR_PROC(0x6bc260);
    COLOR_STATUS_AWAY   = COLOR_PROC(0xcebf45);
    COLOR_STATUS_BUSY   = COLOR_PROC(0xc84e4e);

    //---- Buttons ----
    COLOR_BTN_SUCCESS_BKGRND       = COLOR_STATUS_ONLINE;
    COLOR_BTN_SUCCESS_BKGRND_HOVER = COLOR_PROC(0x76d56a);
    COLOR_BTN_SUCCESS_TEXT         = COLOR_BKGRND_MAIN;
    COLOR_BTN_SUCCESS_TEXT_HOVER   = COLOR_BKGRND_MAIN;

    COLOR_BTN_WARNING_BKGRND       = COLOR_STATUS_AWAY;
    COLOR_BTN_WARNING_BKGRND_HOVER = COLOR_PROC(0xe3d24c);
    COLOR_BTN_WARNING_TEXT         = COLOR_BKGRND_MAIN;
    COLOR_BTN_WARNING_TEXT_HOVER   = COLOR_BKGRND_MAIN;

    COLOR_BTN_DANGER_BACKGROUND   = COLOR_STATUS_BUSY;
    COLOR_BTN_DANGER_BKGRND_HOVER = COLOR_PROC(0xdc5656);
    COLOR_BTN_DANGER_TEXT         = COLOR_BKGRND_MAIN;
    COLOR_BTN_DANGER_TEXT_HOVER   = COLOR_BKGRND_MAIN;

    COLOR_BTN_DISABLED_BKGRND       = COLOR_PROC(0xd1d1d1);
    COLOR_BTN_DISABLED_BKGRND_HOVER = COLOR_BKGRND_LIST_HOVER;
    COLOR_BTN_DISABLED_TEXT         = COLOR_BKGRND_MAIN;
    COLOR_BTN_DISABLED_TRANSFER     = COLOR_BKGRND_LIST;
    COLOR_BTN_DISABLED_FORGRND      = COLOR_PROC(0xb3b3b3);

    COLOR_BTN_INPROGRESS_BKGRND  = COLOR_PROC(0x4ea6ea);
    COLOR_BTN_INPROGRESS_TEXT    = COLOR_BKGRND_MAIN;
    COLOR_BTN_INPROGRESS_FORGRND = COLOR_PROC(0x76baef);

    switch (loadtheme) {
        case THEME_DARK: {
            COLOR_BKGRND_MAIN        = COLOR_PROC(0x333333);
            COLOR_BKGRND_ALT         = COLOR_PROC(0x151515);
            COLOR_BKGRND_LIST        = COLOR_PROC(0x222222);
            COLOR_BKGRND_LIST_HOVER  = COLOR_PROC(0x151515);
            COLOR_BKGRND_MENU        = COLOR_PROC(0x171717);
            COLOR_BKGRND_AUX         = COLOR_BKGRND_MENU;
            COLOR_BKGRND_MENU_HOVER  = COLOR_BKGRND_LIST_HOVER;
            COLOR_BKGRND_MENU_ACTIVE = COLOR_BKGRND_LIST;

            COLOR_MAIN_TEXT         = COLOR_PROC(0xdfdfdf);
            COLOR_MAIN_TEXT_CHAT    = COLOR_PROC(0xffffff);
            COLOR_MAIN_TEXT_SUBTEXT = COLOR_PROC(0xbbbbbb);
            COLOR_MAIN_TEXT_ACTION  = COLOR_PROC(0x27a9bc);
            COLOR_MAIN_TEXT_URL     = COLOR_MAIN_TEXT_ACTION;
            COLOR_MAIN_TEXT_QUOTE   = COLOR_PROC(0x55b317);

            COLOR_MSG_USER       = COLOR_MAIN_TEXT_SUBTEXT;
            COLOR_MSG_USER_PEND  = COLOR_PROC(0x66ccff);
            COLOR_MSG_USER_ERROR = COLOR_MAIN_TEXT_RED;
            COLOR_MSG_CONTACT    = COLOR_MAIN_TEXT;

            COLOR_MENU_TEXT_ACTIVE = COLOR_MAIN_TEXT;

            COLOR_GROUP_MUTED = COLOR_MAIN_TEXT_URL;

            COLOR_SELECTION_BACKGROUND = COLOR_MAIN_TEXT;
            COLOR_SELECTION_TEXT       = COLOR_BKGRND_MAIN;

            COLOR_EDGE_NORMAL         = COLOR_PROC(0x555555);
            COLOR_EDGE_ACTIVE         = COLOR_PROC(0x228888);
            COLOR_EDGE_HOVER          = COLOR_PROC(0x999999);
            COLOR_ACTIVEOPTION_BKGRND = COLOR_PROC(0x228888);
            COLOR_ACTIVEOPTION_TEXT   = COLOR_MAIN_TEXT;

            COLOR_AUX_EDGE_NORMAL         = COLOR_BKGRND_AUX;
            COLOR_AUX_EDGE_ACTIVE         = COLOR_EDGE_ACTIVE;
            COLOR_AUX_ACTIVEOPTION_BKGRND = COLOR_ACTIVEOPTION_BKGRND;

            COLOR_BTN_SUCCESS_BKGRND       = COLOR_PROC(0x414141);
            COLOR_BTN_SUCCESS_TEXT         = COLOR_PROC(0x33a63d);
            COLOR_BTN_SUCCESS_BKGRND_HOVER = COLOR_PROC(0x455147);
            COLOR_BTN_SUCCESS_TEXT_HOVER   = COLOR_PROC(0x6eff3a);

            COLOR_BTN_WARNING_BKGRND       = COLOR_PROC(0x414141);
            COLOR_BTN_WARNING_TEXT         = COLOR_PROC(0xbd9e22);
            COLOR_BTN_WARNING_BKGRND_HOVER = COLOR_PROC(0x4c493c);
            COLOR_BTN_WARNING_TEXT_HOVER   = COLOR_PROC(0xff8d2a);

            COLOR_BTN_DANGER_BACKGROUND   = COLOR_PROC(0x414141);
            COLOR_BTN_DANGER_TEXT         = COLOR_PROC(0xbd2525);
            COLOR_BTN_DANGER_BKGRND_HOVER = COLOR_PROC(0x513939);
            COLOR_BTN_DANGER_TEXT_HOVER   = COLOR_PROC(0xfa2626);

            COLOR_BTN_DISABLED_BKGRND   = COLOR_PROC(0x414141);
            COLOR_BTN_DISABLED_TEXT     = COLOR_MAIN_TEXT;
            COLOR_BTN_DISABLED_TRANSFER = COLOR_BTN_DISABLED_TEXT;
            COLOR_BTN_DISABLED_FORGRND  = COLOR_PROC(0x666666);

            COLOR_BTN_INPROGRESS_BKGRND  = COLOR_BTN_DISABLED_BKGRND;
            COLOR_BTN_INPROGRESS_TEXT    = COLOR_MAIN_TEXT_URL;
            COLOR_BTN_INPROGRESS_FORGRND = COLOR_PROC(0x2f656a);
            break;
        }
        case THEME_LIGHT: {
            COLOR_BKGRND_AUX         = COLOR_PROC(0xe0e0e0);
            COLOR_BKGRND_LIST        = COLOR_PROC(0xf0f0f0);
            COLOR_BKGRND_LIST_HOVER  = COLOR_PROC(0xe0e0e0);
            COLOR_BKGRND_MENU        = COLOR_BKGRND_LIST;
            COLOR_BKGRND_MENU_HOVER  = COLOR_PROC(0xe0e0e0);
            COLOR_BKGRND_MENU_ACTIVE = COLOR_PROC(0x555555);

            COLOR_LIST_TEXT         = COLOR_MAIN_TEXT;
            COLOR_LIST_TEXT_SUBTEXT = COLOR_MAIN_TEXT_SUBTEXT;

            COLOR_MENU_TEXT         = COLOR_PROC(0x555555);
            COLOR_MENU_TEXT_ACTIVE  = COLOR_PROC(0xffffff);
            COLOR_MENU_TEXT_SUBTEXT = COLOR_PROC(0x414141);

            COLOR_EDGE_NORMAL         = COLOR_PROC(0xc0c0c0);
            COLOR_EDGE_HOVER          = COLOR_PROC(0x707070);
            COLOR_ACTIVEOPTION_BKGRND = COLOR_PROC(0xc2e0ff);
            COLOR_ACTIVEOPTION_TEXT   = COLOR_MAIN_TEXT;

            COLOR_AUX_EDGE_NORMAL         = COLOR_BKGRND_AUX;
            COLOR_AUX_EDGE_HOVER          = COLOR_PROC(0x999999);
            COLOR_AUX_EDGE_ACTIVE         = COLOR_EDGE_ACTIVE;
            COLOR_AUX_TEXT                = COLOR_LIST_TEXT;
            COLOR_AUX_ACTIVEOPTION_BKGRND = COLOR_ACTIVEOPTION_BKGRND;
            COLOR_AUX_ACTIVEOPTION_TEXT   = COLOR_AUX_TEXT;
            break;
        }
        case THEME_HIGHCONTRAST: {
          COLOR_BKGRND_MAIN        = COLOR_PROC(FOSSA_MID_GRAY); // Main chat area bg
          COLOR_BKGRND_ALT         = COLOR_PROC(FOSSA_MID_GRAY); // Frame color (above and below the chat area)
          COLOR_BKGRND_AUX         = COLOR_PROC(FOSSA_MID_GRAY); // "Search/Add Friends" bg
          COLOR_BKGRND_LIST        = COLOR_PROC(FOSSA_MID_GRAY); // Contact list bg
          COLOR_BKGRND_LIST_HOVER  = COLOR_PROC(FOSSA_DARK_ORANGE); // Contact list hover bg
          COLOR_BKGRND_MENU        = COLOR_BKGRND_LIST; // Settings gear bg
          COLOR_BKGRND_MENU_HOVER  = COLOR_BKGRND_LIST; // Settings gear hover bg
          COLOR_BKGRND_MENU_ACTIVE = COLOR_BKGRND_LIST; // Settings gear bg when settings opened

          COLOR_MAIN_TEXT         = COLOR_PROC(FOSSA_LIGHT_TEXT); // Contact's avatar and name when selected in contact list and in chat header, keyboard cursor, tooltip text, settings menu text, settings menu tab text, settings menu input box text
          COLOR_MAIN_TEXT_CHAT    = COLOR_MAIN_TEXT;
          COLOR_MAIN_TEXT_SUBTEXT = COLOR_PROC(FOSSA_DARK_TEXT); // Group chat header: "2 users in chat", "Drag friends to invite them", Contact's status messgage in chat header, Contact list status message under the contact's name when they are selected (non selected status message in contact list uses the COLOR_LIST_TEXT_SUBTEXT), your name in chat, timestamp in chat, hover action on settings tabs text
          COLOR_MAIN_TEXT_ACTION  = COLOR_PROC(FOSSA_SPOTLIGHT_TEXT); // System messages: Call started/ended, Friend has changed name, Day has changed, etc.
          COLOR_MAIN_TEXT_QUOTE   = COLOR_MAIN_TEXT_SUBTEXT;
          COLOR_MAIN_TEXT_RED     = COLOR_MAIN_TEXT_RED;
          COLOR_MAIN_TEXT_URL     = COLOR_MAIN_TEXT_ACTION; // Hyperlink in chat
          COLOR_MAIN_TEXT_HINT    = COLOR_MAIN_TEXT_SUBTEXT; // "Search/Add Friends", "IP address", "Port", typing indicator

          COLOR_MSG_USER       = COLOR_MAIN_TEXT; // Own message color that has been delivered
          COLOR_MSG_USER_PEND  = COLOR_MAIN_TEXT_SUBTEXT; // Sent message that has NOT been delivered yet
          COLOR_MSG_USER_ERROR = COLOR_MAIN_TEXT_RED;
          COLOR_MSG_CONTACT    = COLOR_MAIN_TEXT; // Contact's message color

          COLOR_MENU_TEXT         = COLOR_MAIN_TEXT; // Settings gear icon default state, Contact avatars color, Own name in contact list
          COLOR_MENU_TEXT_SUBTEXT = COLOR_MAIN_TEXT_SUBTEXT; // "All contacts" text, "Online contacts" text, your own status message on contact list
          COLOR_MENU_TEXT_ACTIVE  = COLOR_PROC(FOSSA_DARK_PURPLE);; // Settings gear color when settings opened

          COLOR_LIST_TEXT         = COLOR_MAIN_TEXT; // Contact list names
          COLOR_LIST_TEXT_SUBTEXT = COLOR_MAIN_TEXT_SUBTEXT; // Contact list text below the names (status message)

          COLOR_GROUP_SELF  = COLOR_MAIN_TEXT;
          COLOR_GROUP_PEER  = COLOR_MAIN_TEXT;
          COLOR_GROUP_AUDIO = COLOR_MAIN_TEXT_SUBTEXT;
          COLOR_GROUP_MUTED = COLOR_MAIN_TEXT_SUBTEXT;

          COLOR_SELECTION_BACKGROUND = COLOR_PROC(FOSSA_LIGHT_TEXT); // Selected text bg in chat or in input boxes
          COLOR_SELECTION_TEXT       = COLOR_PROC(FOSSA_DARKEST_GRAY); // Selected text font color in chat or input boxes

          COLOR_EDGE_NORMAL         = COLOR_PROC(FOSSA_DARKEST_GRAY); // Settings tab edges, Dropdown menu edges, Text input box edges (IP address, Port, etc), Main Chat area top and bottom edges
          COLOR_EDGE_HOVER          = COLOR_PROC(FOSSA_DARKEST_GRAY); // Dropdown menu edge, Text input box edges (IP address, Port, etc) when hovered
          COLOR_EDGE_ACTIVE         = COLOR_PROC(FOSSA_LIGHT_PURPLE); // Dropdown menu edge when opened, Settings tab top edge when opened, Text input box edges when active (IP address, Port, etc)
          COLOR_ACTIVEOPTION_BKGRND = COLOR_EDGE_ACTIVE; // Dropdown menu hover item bg
          COLOR_ACTIVEOPTION_TEXT   = COLOR_MAIN_TEXT; // Dropdown menu hover item text

          COLOR_AUX_EDGE_NORMAL         = COLOR_EDGE_NORMAL; // "Search/Add Friends" edge
          COLOR_AUX_EDGE_HOVER          = COLOR_EDGE_HOVER; // "Search/Add Friends" hovered edge
          COLOR_AUX_EDGE_ACTIVE         = COLOR_EDGE_ACTIVE; // "Search/Add Friends" input box active edge
          COLOR_AUX_TEXT                = COLOR_MAIN_TEXT; // "Search/Add Friends" input text
          COLOR_AUX_ACTIVEOPTION_BKGRND = COLOR_PROC(0xFFFFFF);
          COLOR_AUX_ACTIVEOPTION_TEXT   = COLOR_PROC(0xFFFFFF);

          COLOR_STATUS_ONLINE = COLOR_PROC(FOSSA_STATUS_GREEN);
          COLOR_STATUS_AWAY   = COLOR_PROC(FOSSA_STATUS_YELLOW);
          COLOR_STATUS_BUSY   = COLOR_PROC(FOSSA_STATUS_RED);

          COLOR_BTN_SUCCESS_BKGRND        = COLOR_PROC(FOSSA_DARK_PURPLE); // Toggle switch "ON" state bg, FileTransfer successfully finished bg, Settings buttons like: "Show password field" bg, Call/FileTransfer/Send message buttons bg in normal state
          COLOR_BTN_SUCCESS_TEXT          = COLOR_PROC(FOSSA_LIGHT_GRAY); // Toggle switch "ON" state tick and rounded rectangle color, FileTransfer successfully finished text: "click to open" and filename, Settings buttons like: "Show password field" text, Call/FileTransfer/Send message button icons in normal state
          COLOR_BTN_SUCCESS_BKGRND_HOVER  = COLOR_PROC(FOSSA_LIGHT_PURPLE); // Same as above but for hover
          COLOR_BTN_SUCCESS_TEXT_HOVER    = COLOR_BTN_SUCCESS_TEXT; // Same as above but for hover

          COLOR_BTN_WARNING_BKGRND        = COLOR_PROC(REAPER_GREEN1); // Call button bg during an incoming call
          COLOR_BTN_WARNING_TEXT          = COLOR_MAIN_TEXT; // Call button icon color during an incoming call
          COLOR_BTN_WARNING_BKGRND_HOVER  = COLOR_PROC(REAPER_GREEN1); // Same as above but for hover
          COLOR_BTN_WARNING_TEXT_HOVER    = COLOR_PROC(REAPER_GREEN4); // Same as above but for hover

          COLOR_BTN_DANGER_BACKGROUND     = COLOR_PROC(REAPER_GREEN1); // Call button bg during outgoing call and during esablished call
          COLOR_BTN_DANGER_TEXT           = COLOR_MAIN_TEXT; // Call button icon color during outgoing call and during esablished call
          COLOR_BTN_DANGER_BKGRND_HOVER   = COLOR_PROC(REAPER_GREEN1); // Same as above but for hover
          COLOR_BTN_DANGER_TEXT_HOVER     = COLOR_PROC(REAPER_GREEN4); // Same as above but for hover

          COLOR_BTN_DISABLED_BKGRND       = COLOR_PROC(FOSSA_DARK_GRAY); // Toggle switch "OFF" state bg, FileTransfer failed or cancelled bg, call/filesend/send message buttons when contact is offline, though you can still click on send message and it will be delivered when user comes online
          COLOR_BTN_DISABLED_TEXT         = COLOR_PROC(FOSSA_LIGHT_GRAY); // Toggle switch "OFF" state "X" and rounded rectangle, FileTransfer failed or cancelled text
          COLOR_BTN_DISABLED_BKGRND_HOVER = COLOR_BTN_DISABLED_BKGRND; // Same as above but for hover
          COLOR_BTN_DISABLED_TRANSFER     = COLOR_BKGRND_LIST;
          COLOR_BTN_DISABLED_FORGRND      = COLOR_BTN_DISABLED_TEXT;

          COLOR_BTN_INPROGRESS_FORGRND = COLOR_PROC(FOSSA_LIGHT_PURPLE); // FileTransfer progress bar: transfer progress
          COLOR_BTN_INPROGRESS_BKGRND  = COLOR_PROC(FOSSA_DARK_PURPLE); // FileTransfer progress bar: bg
          COLOR_BTN_INPROGRESS_TEXT    = COLOR_MAIN_TEXT; // FileTransfer progress bar text
            break;
        }
        case THEME_ZENBURN: {
          COLOR_BKGRND_MAIN        = COLOR_PROC(MOJAVE_GRAY1); // Main chat area bg
          COLOR_BKGRND_ALT         = COLOR_PROC(MOJAVE_GRAY2); // Frame color (above and below the chat area)
          COLOR_BKGRND_AUX         = COLOR_PROC(MOJAVE_GRAY2); // "Search/Add Friends" bg
          COLOR_BKGRND_LIST        = COLOR_PROC(MOJAVE_GRAY2); // Contact list bg
          COLOR_BKGRND_LIST_HOVER  = COLOR_PROC(MOJAVE_GRAY5); // Contact list hover bg
          COLOR_BKGRND_MENU        = COLOR_BKGRND_LIST; // Settings gear bg
          COLOR_BKGRND_MENU_HOVER  = COLOR_BKGRND_LIST; // Settings gear hover bg
          COLOR_BKGRND_MENU_ACTIVE = COLOR_BKGRND_LIST; // Settings gear bg when settings opened

          COLOR_MAIN_TEXT         = COLOR_PROC(MOJAVE_GRAY3); // Contact's avatar and name when selected in contact list and in chat header, keyboard cursor, tooltip text, settings menu text, settings menu tab text, settings menu input box text
          COLOR_MAIN_TEXT_CHAT    = COLOR_MAIN_TEXT;
          COLOR_MAIN_TEXT_SUBTEXT = COLOR_PROC(MOJAVE_GRAY4); // Group chat header: "2 users in chat", "Drag friends to invite them", Contact's status messgage in chat header, Contact list status message under the contact's name when they are selected (non selected status message in contact list uses the COLOR_LIST_TEXT_SUBTEXT), your name in chat, timestamp in chat, hover action on settings tabs text
          COLOR_MAIN_TEXT_ACTION  = COLOR_PROC(REAPER_GREEN3); // System messages: Call started/ended, Friend has changed name, Day has changed, etc.
          COLOR_MAIN_TEXT_QUOTE   = COLOR_MAIN_TEXT_SUBTEXT;
          COLOR_MAIN_TEXT_RED     = COLOR_MAIN_TEXT_RED;
          COLOR_MAIN_TEXT_URL     = COLOR_MAIN_TEXT_ACTION; // Hyperlink in chat
          COLOR_MAIN_TEXT_HINT    = COLOR_MAIN_TEXT_SUBTEXT; // "Search/Add Friends", "IP address", "Port", typing indicator

          COLOR_MSG_USER       = COLOR_MAIN_TEXT; // Own message color that has been delivered
          COLOR_MSG_USER_PEND  = COLOR_MAIN_TEXT_SUBTEXT; // Sent message that has NOT been delivered yet
          COLOR_MSG_USER_ERROR = COLOR_MAIN_TEXT_RED;
          COLOR_MSG_CONTACT    = COLOR_MAIN_TEXT; // Contact's message color

          COLOR_MENU_TEXT         = COLOR_MAIN_TEXT; // Settings gear icon default state, Contact avatars color, Own name in contact list
          COLOR_MENU_TEXT_SUBTEXT = COLOR_MAIN_TEXT_SUBTEXT; // "All contacts" text, "Online contacts" text, your own status message on contact list
          COLOR_MENU_TEXT_ACTIVE  = COLOR_PROC(REAPER_GREEN3);; // Settings gear color when settings opened

          COLOR_LIST_TEXT         = COLOR_MAIN_TEXT; // Contact list names
          COLOR_LIST_TEXT_SUBTEXT = COLOR_MAIN_TEXT_SUBTEXT; // Contact list text below the names (status message)

          COLOR_GROUP_SELF  = COLOR_MAIN_TEXT;
          COLOR_GROUP_PEER  = COLOR_MAIN_TEXT;
          COLOR_GROUP_AUDIO = COLOR_MAIN_TEXT_SUBTEXT;
          COLOR_GROUP_MUTED = COLOR_MAIN_TEXT_SUBTEXT;

          COLOR_SELECTION_BACKGROUND = COLOR_PROC(MOJAVE_GRAY8); // Selected text bg in chat or in input boxes
          COLOR_SELECTION_TEXT       = COLOR_PROC(MOJAVE_GRAY4); // Selected text font color in chat or input boxes

          COLOR_EDGE_NORMAL         = COLOR_PROC(MOJAVE_GRAY8); // Settings tab edges, Dropdown menu edges, Text input box edges (IP address, Port, etc), Main Chat area top and bottom edges
          COLOR_EDGE_HOVER          = COLOR_PROC(MOJAVE_GRAY8); // Dropdown menu edge, Text input box edges (IP address, Port, etc) when hovered
          COLOR_EDGE_ACTIVE         = COLOR_PROC(MOJAVE_GRAY8); // Dropdown menu edge when opened, Settings tab top edge when opened, Text input box edges when active (IP address, Port, etc)
          COLOR_ACTIVEOPTION_BKGRND = COLOR_EDGE_ACTIVE; // Dropdown menu hover item bg
          COLOR_ACTIVEOPTION_TEXT   = COLOR_MAIN_TEXT; // Dropdown menu hover item text

          COLOR_AUX_EDGE_NORMAL         = COLOR_PROC(REAPER_GREEN2); // "Search/Add Friends" edge
          COLOR_AUX_EDGE_HOVER          = COLOR_PROC(REAPER_GREEN4); // "Search/Add Friends" hovered edge
          COLOR_AUX_EDGE_ACTIVE         = COLOR_PROC(REAPER_GREEN3); // "Search/Add Friends" input box active edge
          COLOR_AUX_TEXT                = COLOR_MAIN_TEXT; // "Search/Add Friends" input text
          COLOR_AUX_ACTIVEOPTION_BKGRND = COLOR_PROC(0xFFFFFF);
          COLOR_AUX_ACTIVEOPTION_TEXT   = COLOR_PROC(0xFFFFFF);

          COLOR_STATUS_ONLINE = COLOR_PROC(MOJAVE_STATUS_GREEN);
          COLOR_STATUS_AWAY   = COLOR_PROC(MOJAVE_STATUS_YELLOW);
          COLOR_STATUS_BUSY   = COLOR_PROC(MOJAVE_STATUS_RED);

          COLOR_BTN_SUCCESS_BKGRND        = COLOR_PROC(REAPER_GREEN1); // Toggle switch "ON" state bg, FileTransfer successfully finished bg, Settings buttons like: "Show password field" bg, Call/FileTransfer/Send message buttons bg in normal state
          COLOR_BTN_SUCCESS_TEXT          = COLOR_PROC(REAPER_GREEN3); // Toggle switch "ON" state tick and rounded rectangle color, FileTransfer successfully finished text: "click to open" and filename, Settings buttons like: "Show password field" text, Call/FileTransfer/Send message button icons in normal state
          COLOR_BTN_SUCCESS_BKGRND_HOVER  = COLOR_PROC(REAPER_GREEN1); // Same as above but for hover
          COLOR_BTN_SUCCESS_TEXT_HOVER    = COLOR_PROC(REAPER_GREEN4); // Same as above but for hover

          COLOR_BTN_WARNING_BKGRND        = COLOR_PROC(REAPER_GREEN1); // Call button bg during an incoming call
          COLOR_BTN_WARNING_TEXT          = COLOR_MAIN_TEXT; // Call button icon color during an incoming call
          COLOR_BTN_WARNING_BKGRND_HOVER  = COLOR_PROC(REAPER_GREEN1); // Same as above but for hover
          COLOR_BTN_WARNING_TEXT_HOVER    = COLOR_PROC(REAPER_GREEN4); // Same as above but for hover

          COLOR_BTN_DANGER_BACKGROUND     = COLOR_PROC(REAPER_GREEN1); // Call button bg during outgoing call and during esablished call
          COLOR_BTN_DANGER_TEXT           = COLOR_MAIN_TEXT; // Call button icon color during outgoing call and during esablished call
          COLOR_BTN_DANGER_BKGRND_HOVER   = COLOR_PROC(REAPER_GREEN1); // Same as above but for hover
          COLOR_BTN_DANGER_TEXT_HOVER     = COLOR_PROC(REAPER_GREEN4); // Same as above but for hover

          COLOR_BTN_DISABLED_BKGRND       = COLOR_PROC(REAPER_GREEN1); // Toggle switch "OFF" state bg, FileTransfer failed or cancelled bg, call/filesend/send message buttons when contact is offline, though you can still click on send message and it will be delivered when user comes online
          COLOR_BTN_DISABLED_TEXT         = COLOR_PROC(REAPER_GREEN3); // Toggle switch "OFF" state "X" and rounded rectangle, FileTransfer failed or cancelled text
          COLOR_BTN_DISABLED_BKGRND_HOVER = COLOR_PROC(REAPER_GREEN1); // Same as above but for hover
          COLOR_BTN_DISABLED_TRANSFER     = COLOR_BKGRND_LIST;
          COLOR_BTN_DISABLED_FORGRND      = COLOR_PROC(REAPER_GRAY0);

          COLOR_BTN_INPROGRESS_FORGRND = COLOR_PROC(REAPER_GREEN3); // FileTransfer progress bar: transfer progress
          COLOR_BTN_INPROGRESS_BKGRND  = COLOR_PROC(REAPER_GRAY0); // FileTransfer progress bar: bg
          COLOR_BTN_INPROGRESS_TEXT    = COLOR_MAIN_TEXT; // FileTransfer progress bar text
            break;
        }
        case THEME_SOLARIZED_DARK: {
          COLOR_BKGRND_MAIN        = COLOR_PROC(REAPER_GRAY0); // Main chat area bg
          COLOR_BKGRND_ALT         = COLOR_PROC(REAPER_GRAY1); // Frame color (above and below the chat area)
          COLOR_BKGRND_AUX         = COLOR_PROC(REAPER_GRAY1); // "Search/Add Friends" bg
          COLOR_BKGRND_LIST        = COLOR_PROC(REAPER_GRAY1); // Contact list bg
          COLOR_BKGRND_LIST_HOVER  = COLOR_PROC(REAPER_GRAY2); // Contact list hover bg
          COLOR_BKGRND_MENU        = COLOR_BKGRND_LIST; // Settings gear bg
          COLOR_BKGRND_MENU_HOVER  = COLOR_BKGRND_LIST; // Settings gear hover bg
          COLOR_BKGRND_MENU_ACTIVE = COLOR_BKGRND_LIST; // Settings gear bg when settings opened

          COLOR_MAIN_TEXT         = COLOR_PROC(REAPER_GRAY7); // Contact's avatar and name when selected in contact list and in chat header, keyboard cursor, tooltip text, settings menu text, settings menu tab text, settings menu input box text
          COLOR_MAIN_TEXT_CHAT    = COLOR_MAIN_TEXT;
          COLOR_MAIN_TEXT_SUBTEXT = COLOR_PROC(REAPER_GRAY6); // Group chat header: "2 users in chat", "Drag friends to invite them", Contact's status messgage in chat header, Contact list status message under the contact's name when they are selected (non selected status message in contact list uses the COLOR_LIST_TEXT_SUBTEXT), your name in chat, timestamp in chat, hover action on settings tabs text
          COLOR_MAIN_TEXT_ACTION  = COLOR_PROC(REAPER_GREEN3); // System messages: Call started/ended, Friend has changed name, Day has changed, etc.
          COLOR_MAIN_TEXT_QUOTE   = COLOR_MAIN_TEXT_SUBTEXT;
          COLOR_MAIN_TEXT_RED     = COLOR_MAIN_TEXT_RED;
          COLOR_MAIN_TEXT_URL     = COLOR_MAIN_TEXT_ACTION; // Hyperlink in chat
          COLOR_MAIN_TEXT_HINT    = COLOR_MAIN_TEXT_SUBTEXT; // "Search/Add Friends", "IP address", "Port", typing indicator

          COLOR_MSG_USER       = COLOR_MAIN_TEXT; // Own message color that has been delivered
          COLOR_MSG_USER_PEND  = COLOR_MAIN_TEXT_SUBTEXT; // Sent message that has NOT been delivered yet
          COLOR_MSG_USER_ERROR = COLOR_MAIN_TEXT_RED;
          COLOR_MSG_CONTACT    = COLOR_MAIN_TEXT; // Contact's message color

          COLOR_MENU_TEXT         = COLOR_MAIN_TEXT; // Settings gear icon default state, Contact avatars color, Own name in contact list
          COLOR_MENU_TEXT_SUBTEXT = COLOR_MAIN_TEXT_SUBTEXT; // "All contacts" text, "Online contacts" text, your own status message on contact list
          COLOR_MENU_TEXT_ACTIVE  = COLOR_PROC(REAPER_GREEN3);; // Settings gear color when settings opened

          COLOR_LIST_TEXT         = COLOR_MAIN_TEXT; // Contact list names
          COLOR_LIST_TEXT_SUBTEXT = COLOR_MAIN_TEXT_SUBTEXT; // Contact list text below the names (status message)

          COLOR_GROUP_SELF  = COLOR_MAIN_TEXT;
          COLOR_GROUP_PEER  = COLOR_MAIN_TEXT;
          COLOR_GROUP_AUDIO = COLOR_MAIN_TEXT_SUBTEXT;
          COLOR_GROUP_MUTED = COLOR_MAIN_TEXT_SUBTEXT;

          COLOR_SELECTION_BACKGROUND = COLOR_PROC(REAPER_GREEN2); // Selected text bg in chat or in input boxes
          COLOR_SELECTION_TEXT       = COLOR_PROC(REAPER_GRAY5); // Selected text font color in chat or input boxes

          COLOR_EDGE_NORMAL         = COLOR_PROC(REAPER_GREEN2); // Settings tab edges, Dropdown menu edges, Text input box edges (IP address, Port, etc), Main Chat area top and bottom edges
          COLOR_EDGE_HOVER          = COLOR_PROC(REAPER_GREEN4); // Dropdown menu edge, Text input box edges (IP address, Port, etc) when hovered
          COLOR_EDGE_ACTIVE         = COLOR_PROC(REAPER_GREEN3); // Dropdown menu edge when opened, Settings tab top edge when opened, Text input box edges when active (IP address, Port, etc)
          COLOR_ACTIVEOPTION_BKGRND = COLOR_EDGE_ACTIVE; // Dropdown menu hover item bg
          COLOR_ACTIVEOPTION_TEXT   = COLOR_MAIN_TEXT; // Dropdown menu hover item text

          COLOR_AUX_EDGE_NORMAL         = COLOR_EDGE_NORMAL; // "Search/Add Friends" edge
          COLOR_AUX_EDGE_HOVER          = COLOR_EDGE_HOVER; // "Search/Add Friends" hovered edge
          COLOR_AUX_EDGE_ACTIVE         = COLOR_EDGE_ACTIVE; // "Search/Add Friends" input box active edge
          COLOR_AUX_TEXT                = COLOR_MAIN_TEXT; // "Search/Add Friends" input text
          COLOR_AUX_ACTIVEOPTION_BKGRND = COLOR_BKGRND_AUX;
          COLOR_AUX_ACTIVEOPTION_TEXT   = COLOR_MAIN_TEXT;

          COLOR_STATUS_ONLINE = COLOR_PROC(REAPER_STATUS_GREEN);
          COLOR_STATUS_AWAY   = COLOR_PROC(REAPER_STATUS_YELLOW);
          COLOR_STATUS_BUSY   = COLOR_PROC(REAPER_STATUS_RED);

          COLOR_BTN_SUCCESS_BKGRND        = COLOR_PROC(REAPER_GREEN1); // Toggle switch "ON" state bg, FileTransfer successfully finished bg, Settings buttons like: "Show password field" bg, Call/FileTransfer/Send message buttons bg in normal state
          COLOR_BTN_SUCCESS_TEXT          = COLOR_PROC(REAPER_GREEN3); // Toggle switch "ON" state tick and rounded rectangle color, FileTransfer successfully finished text: "click to open" and filename, Settings buttons like: "Show password field" text, Call/FileTransfer/Send message button icons in normal state
          COLOR_BTN_SUCCESS_BKGRND_HOVER  = COLOR_PROC(REAPER_GREEN1); // Same as above but for hover
          COLOR_BTN_SUCCESS_TEXT_HOVER    = COLOR_PROC(REAPER_GREEN4); // Same as above but for hover

          COLOR_BTN_WARNING_BKGRND        = COLOR_PROC(REAPER_GREEN1); // Call button bg during an incoming call
          COLOR_BTN_WARNING_TEXT          = COLOR_MAIN_TEXT; // Call button icon color during an incoming call
          COLOR_BTN_WARNING_BKGRND_HOVER  = COLOR_PROC(REAPER_GREEN1); // Same as above but for hover
          COLOR_BTN_WARNING_TEXT_HOVER    = COLOR_PROC(REAPER_GREEN4); // Same as above but for hover

          COLOR_BTN_DANGER_BACKGROUND     = COLOR_PROC(REAPER_GREEN1); // Call button bg during outgoing call and during esablished call
          COLOR_BTN_DANGER_TEXT           = COLOR_MAIN_TEXT; // Call button icon color during outgoing call and during esablished call
          COLOR_BTN_DANGER_BKGRND_HOVER   = COLOR_PROC(REAPER_GREEN1); // Same as above but for hover
          COLOR_BTN_DANGER_TEXT_HOVER     = COLOR_PROC(REAPER_GREEN4); // Same as above but for hover

          COLOR_BTN_DISABLED_BKGRND       = COLOR_PROC(REAPER_GREEN1); // Toggle switch "OFF" state bg, FileTransfer failed or cancelled bg, call/filesend/send message buttons when contact is offline, though you can still click on send message and it will be delivered when user comes online
          COLOR_BTN_DISABLED_TEXT         = COLOR_PROC(REAPER_GREEN3); // Toggle switch "OFF" state "X" and rounded rectangle, FileTransfer failed or cancelled text
          COLOR_BTN_DISABLED_BKGRND_HOVER = COLOR_PROC(REAPER_GREEN1); // Same as above but for hover
          COLOR_BTN_DISABLED_TRANSFER     = COLOR_BKGRND_LIST;
          COLOR_BTN_DISABLED_FORGRND      = COLOR_PROC(REAPER_GRAY0);

          COLOR_BTN_INPROGRESS_FORGRND = COLOR_MAIN_TEXT_ACTION; // FileTransfer progress bar: transfer progress
          COLOR_BTN_INPROGRESS_BKGRND  = COLOR_PROC(REAPER_GRAY0); // FileTransfer progress bar: bg
          COLOR_BTN_INPROGRESS_TEXT    = COLOR_MAIN_TEXT; // FileTransfer progress bar text
            break;
        }
        case THEME_SOLARIZED_LIGHT: {
          COLOR_BKGRND_MAIN        = COLOR_PROC(ATOM_GRAYBLUE3); // Main chat area bg
          COLOR_BKGRND_ALT         = COLOR_PROC(ATOM_GRAYBLUE1); // Frame color (above and below the chat area)
          COLOR_BKGRND_AUX         = COLOR_PROC(ATOM_GRAYBLUE1); // "Search/Add Friends" bg
          COLOR_BKGRND_LIST        = COLOR_PROC(ATOM_GRAYBLUE1); // Contact list bg
          COLOR_BKGRND_LIST_HOVER  = COLOR_PROC(ATOM_GRAYBLUE1); // Contact list hover bg
          COLOR_BKGRND_MENU        = COLOR_BKGRND_LIST; // Settings gear bg
          COLOR_BKGRND_MENU_HOVER  = COLOR_BKGRND_LIST; // Settings gear hover bg
          COLOR_BKGRND_MENU_ACTIVE = COLOR_BKGRND_LIST; // Settings gear bg when settings opened

          COLOR_MAIN_TEXT         = COLOR_PROC(ATOM_GRAYBLUE9); // Contact's avatar and name when selected in contact list and in chat header, keyboard cursor, tooltip text, settings menu text, settings menu tab text, settings menu input box text
          COLOR_MAIN_TEXT_CHAT    = COLOR_MAIN_TEXT;
          COLOR_MAIN_TEXT_SUBTEXT = COLOR_PROC(ATOM_GRAYBLUE8); // Group chat header: "2 users in chat", "Drag friends to invite them", Contact's status messgage in chat header, Contact list status message under the contact's name when they are selected (non selected status message in contact list uses the COLOR_LIST_TEXT_SUBTEXT), your name in chat, timestamp in chat, hover action on settings tabs text
          COLOR_MAIN_TEXT_ACTION  = COLOR_PROC(ATOM_BLUE); // System messages: Call started/ended, Friend has changed name, Day has changed, etc.
          COLOR_MAIN_TEXT_QUOTE   = COLOR_MAIN_TEXT_SUBTEXT;
          COLOR_MAIN_TEXT_RED     = COLOR_MAIN_TEXT_RED;
          COLOR_MAIN_TEXT_URL     = COLOR_MAIN_TEXT_ACTION; // Hyperlink in chat
          COLOR_MAIN_TEXT_HINT    = COLOR_MAIN_TEXT_SUBTEXT; // "Search/Add Friends", "IP address", "Port", typing indicator

          COLOR_MSG_USER       = COLOR_MAIN_TEXT; // Own message color that has been delivered
          COLOR_MSG_USER_PEND  = COLOR_MAIN_TEXT_SUBTEXT; // Sent message that has NOT been delivered yet
          COLOR_MSG_USER_ERROR = COLOR_MAIN_TEXT_RED;
          COLOR_MSG_CONTACT    = COLOR_MAIN_TEXT; // Contact's message color

          COLOR_MENU_TEXT         = COLOR_MAIN_TEXT; // Settings gear icon default state, Contact avatars color, Own name in contact list
          COLOR_MENU_TEXT_SUBTEXT = COLOR_MAIN_TEXT_SUBTEXT; // "All contacts" text, "Online contacts" text, your own status message on contact list
          COLOR_MENU_TEXT_ACTIVE  = COLOR_PROC(ATOM_BLUE);; // Settings gear color when settings opened

          COLOR_LIST_TEXT         = COLOR_MAIN_TEXT; // Contact list names
          COLOR_LIST_TEXT_SUBTEXT = COLOR_MAIN_TEXT_SUBTEXT; // Contact list text below the names (status message)

          COLOR_GROUP_SELF  = COLOR_MAIN_TEXT;
          COLOR_GROUP_PEER  = COLOR_MAIN_TEXT;
          COLOR_GROUP_AUDIO = COLOR_MAIN_TEXT_SUBTEXT;
          COLOR_GROUP_MUTED = COLOR_MAIN_TEXT_SUBTEXT;

          COLOR_SELECTION_BACKGROUND = COLOR_PROC(ATOM_GRAYBLUE4); // Selected text bg in chat or in input boxes
          COLOR_SELECTION_TEXT       = COLOR_PROC(ATOM_GRAYBLUE5); // Selected text font color in chat or input boxes

          COLOR_EDGE_NORMAL         = COLOR_PROC(ATOM_GRAYBLUE7); // Settings tab edges, Dropdown menu edges, Text input box edges (IP address, Port, etc), Main Chat area top and bottom edges
          COLOR_EDGE_HOVER          = COLOR_PROC(ATOM_GRAYBLUE8); // Dropdown menu edge, Text input box edges (IP address, Port, etc) when hovered
          COLOR_EDGE_ACTIVE         = COLOR_PROC(ATOM_BLUE); // Dropdown menu edge when opened, Settings tab top edge when opened, Text input box edges when active (IP address, Port, etc)
          COLOR_ACTIVEOPTION_BKGRND = COLOR_EDGE_ACTIVE; // Dropdown menu hover item bg
          COLOR_ACTIVEOPTION_TEXT   = COLOR_MAIN_TEXT; // Dropdown menu hover item text

          COLOR_AUX_EDGE_NORMAL         = COLOR_EDGE_NORMAL; // "Search/Add Friends" edge
          COLOR_AUX_EDGE_HOVER          = COLOR_EDGE_HOVER; // "Search/Add Friends" hovered edge
          COLOR_AUX_EDGE_ACTIVE         = COLOR_EDGE_ACTIVE; // "Search/Add Friends" input box active edge
          COLOR_AUX_TEXT                = COLOR_MAIN_TEXT; // "Search/Add Friends" input text
          COLOR_AUX_ACTIVEOPTION_BKGRND = COLOR_BKGRND_AUX;
          COLOR_AUX_ACTIVEOPTION_TEXT   = COLOR_MAIN_TEXT;

          COLOR_STATUS_ONLINE = COLOR_PROC(ATOM_BLUE);
          COLOR_STATUS_AWAY   = COLOR_PROC(ATOM_STATUS_YELLOW);
          COLOR_STATUS_BUSY   = COLOR_PROC(ATOM_STATUS_RED);

          COLOR_BTN_SUCCESS_BKGRND        = COLOR_PROC(ATOM_BLUE); // Toggle switch "ON" state bg, FileTransfer successfully finished bg, Settings buttons like: "Show password field" bg, Call/FileTransfer/Send message buttons bg in normal state
          COLOR_BTN_SUCCESS_TEXT          = COLOR_PROC(ATOM_GRAYBLUE0); // Toggle switch "ON" state tick and rounded rectangle color, FileTransfer successfully finished text: "click to open" and filename, Settings buttons like: "Show password field" text, Call/FileTransfer/Send message button icons in normal state
          COLOR_BTN_SUCCESS_BKGRND_HOVER  = COLOR_PROC(ATOM_BLUE); // Same as above but for hover
          COLOR_BTN_SUCCESS_TEXT_HOVER    = COLOR_PROC(ATOM_GRAYBLUE0); // Same as above but for hover

          COLOR_BTN_WARNING_BKGRND        = COLOR_PROC(ATOM_GRAYBLUE5); // Call button bg during an incoming call
          COLOR_BTN_WARNING_TEXT          = COLOR_MAIN_TEXT; // Call button icon color during an incoming call
          COLOR_BTN_WARNING_BKGRND_HOVER  = COLOR_PROC(ATOM_GRAYBLUE5); // Same as above but for hover
          COLOR_BTN_WARNING_TEXT_HOVER    = COLOR_MAIN_TEXT; // Same as above but for hover

          COLOR_BTN_DANGER_BACKGROUND     = COLOR_PROC(ATOM_GRAYBLUE0); // Call button bg during outgoing call and during esablished call
          COLOR_BTN_DANGER_TEXT           = COLOR_MAIN_TEXT; // Call button icon color during outgoing call and during esablished call
          COLOR_BTN_DANGER_BKGRND_HOVER   = COLOR_PROC(ATOM_GRAYBLUE0); // Same as above but for hover
          COLOR_BTN_DANGER_TEXT_HOVER     = COLOR_MAIN_TEXT; // Same as above but for hover

          COLOR_BTN_DISABLED_BKGRND       = COLOR_PROC(ATOM_GRAYBLUE0); // Toggle switch "OFF" state bg, FileTransfer failed or cancelled bg, call/filesend/send message buttons when contact is offline, though you can still click on send message and it will be delivered when user comes online
          COLOR_BTN_DISABLED_TEXT         = COLOR_MAIN_TEXT; // Toggle switch "OFF" state "X" and rounded rectangle, FileTransfer failed or cancelled text
          COLOR_BTN_DISABLED_BKGRND_HOVER = COLOR_PROC(ATOM_GRAYBLUE0); // Same as above but for hover
          COLOR_BTN_DISABLED_TRANSFER     = COLOR_BKGRND_LIST;
          COLOR_BTN_DISABLED_FORGRND      = COLOR_PROC(REAPER_GRAY0);

          COLOR_BTN_INPROGRESS_FORGRND = COLOR_MAIN_TEXT_ACTION; // FileTransfer progress bar: transfer progress
          COLOR_BTN_INPROGRESS_BKGRND  = COLOR_PROC(REAPER_GRAY0); // FileTransfer progress bar: bg
          COLOR_BTN_INPROGRESS_TEXT    = COLOR_MAIN_TEXT; // FileTransfer progress bar text
            break;
        }
        case THEME_MONOKAI: {
            COLOR_BKGRND_MAIN        = COLOR_PROC(MONOKAI_BROWN1); // Main chat area bg
            COLOR_BKGRND_ALT         = COLOR_PROC(MONOKAI_BROWN0); // Frame color (above and below the chat area)
            COLOR_BKGRND_AUX         = COLOR_PROC(MONOKAI_BROWN0); // "Search/Add Friends" bg
            COLOR_BKGRND_LIST        = COLOR_PROC(MONOKAI_BROWN0); // Contact list bg
            COLOR_BKGRND_LIST_HOVER  = COLOR_PROC(MONOKAI_BROWN1); // Contact list hover bg
            COLOR_BKGRND_MENU        = COLOR_BKGRND_LIST; // Settings gear bg
            COLOR_BKGRND_MENU_HOVER  = COLOR_BKGRND_LIST; // Settings gear hover bg
            COLOR_BKGRND_MENU_ACTIVE = COLOR_BKGRND_LIST; // Settings gear bg when settings opened

            COLOR_MAIN_TEXT         = COLOR_PROC(MONOKAI_WHITE); // Contact's avatar and name when selected in contact list and in chat header, keyboard cursor, tooltip text, settings menu text, settings menu tab text, settings menu input box text
            COLOR_MAIN_TEXT_CHAT    = COLOR_MAIN_TEXT;
            COLOR_MAIN_TEXT_SUBTEXT = COLOR_PROC(MONOKAI_GRAY1); // Group chat header: "2 users in chat", "Drag friends to invite them", Contact's status messgage in chat header, Contact list status message under the contact's name when they are selected (non selected status message in contact list uses the COLOR_LIST_TEXT_SUBTEXT), your name in chat, timestamp in chat, hover action on settings tabs text
            COLOR_MAIN_TEXT_ACTION  = COLOR_PROC(MONOKAI_ORANGE3); // System messages: Call started/ended, Friend has changed name, Day has changed, etc.
            COLOR_MAIN_TEXT_QUOTE   = COLOR_MAIN_TEXT_SUBTEXT;
            COLOR_MAIN_TEXT_RED     = COLOR_MAIN_TEXT_RED;
            COLOR_MAIN_TEXT_URL     = COLOR_MAIN_TEXT_ACTION; // Hyperlink in chat
            COLOR_MAIN_TEXT_HINT    = COLOR_MAIN_TEXT_SUBTEXT; // "Search/Add Friends", "IP address", "Port", typing indicator

            COLOR_MSG_USER       = COLOR_MAIN_TEXT; // Own message color that has been delivered
            COLOR_MSG_USER_PEND  = COLOR_MAIN_TEXT_SUBTEXT; // Sent message that has NOT been delivered yet
            COLOR_MSG_USER_ERROR = COLOR_MAIN_TEXT_RED;
            COLOR_MSG_CONTACT    = COLOR_MAIN_TEXT; // Contact's message color

            COLOR_MENU_TEXT         = COLOR_MAIN_TEXT; // Settings gear icon default state, Contact avatars color, Own name in contact list
            COLOR_MENU_TEXT_SUBTEXT = COLOR_MAIN_TEXT_SUBTEXT; // "All contacts" text, "Online contacts" text, your own status message on contact list
            COLOR_MENU_TEXT_ACTIVE  = COLOR_PROC(MONOKAI_ORANGE3); // Settings gear color when settings opened

            COLOR_LIST_TEXT         = COLOR_MAIN_TEXT; // Contact list names
            COLOR_LIST_TEXT_SUBTEXT = COLOR_MAIN_TEXT_SUBTEXT; // Contact list text below the names (status message)

            COLOR_GROUP_SELF  = COLOR_MAIN_TEXT;
            COLOR_GROUP_PEER  = COLOR_MAIN_TEXT;
            COLOR_GROUP_AUDIO = COLOR_MAIN_TEXT_SUBTEXT;
            COLOR_GROUP_MUTED = COLOR_MAIN_TEXT_SUBTEXT;

            COLOR_SELECTION_BACKGROUND = COLOR_PROC(MONOKAI_ORANGE1); // Selected text bg in chat or in input boxes
            COLOR_SELECTION_TEXT       = COLOR_MAIN_TEXT; // Selected text font color in chat or input boxes

			      COLOR_EDGE_NORMAL         = COLOR_PROC(MONOKAI_GRAY4); // Settings tab edges, Dropdown menu edges, Text input box edges (IP address, Port, etc), Main Chat area top and bottom edges
            COLOR_EDGE_HOVER          = COLOR_PROC(MONOKAI_GRAY5); // Dropdown menu edge, Text input box edges (IP address, Port, etc) when hovered
            COLOR_EDGE_ACTIVE         = COLOR_PROC(MONOKAI_ORANGE3); // Dropdown menu edge when opened, Settings tab top edge when opened, Text input box edges when active (IP address, Port, etc)
            COLOR_ACTIVEOPTION_BKGRND = COLOR_EDGE_ACTIVE; // Dropdown menu hover item bg
            COLOR_ACTIVEOPTION_TEXT   = COLOR_MAIN_TEXT; // Dropdown menu hover item text

            COLOR_AUX_EDGE_NORMAL         = COLOR_EDGE_NORMAL; // "Search/Add Friends" edge
            COLOR_AUX_EDGE_HOVER          = COLOR_EDGE_HOVER; // "Search/Add Friends" hovered edge
            COLOR_AUX_EDGE_ACTIVE         = COLOR_EDGE_ACTIVE; // "Search/Add Friends" input box active edge
            COLOR_AUX_TEXT                = COLOR_MAIN_TEXT; // "Search/Add Friends" input text
            COLOR_AUX_ACTIVEOPTION_BKGRND = COLOR_BKGRND_AUX;
            COLOR_AUX_ACTIVEOPTION_TEXT   = COLOR_MAIN_TEXT;

            COLOR_STATUS_ONLINE = COLOR_PROC(MONOKAI_STATUS_GREEN);
            COLOR_STATUS_AWAY   = COLOR_PROC(MONOKAI_STATUS_YELLOW);
            COLOR_STATUS_BUSY   = COLOR_PROC(MONOKAI_STATUS_RED);

            COLOR_BTN_SUCCESS_BKGRND        = COLOR_PROC(MONOKAI_GRAY4); // Toggle switch "ON" state bg, FileTransfer successfully finished bg, Settings buttons like: "Show password field" bg, Call/FileTransfer/Send message buttons bg in normal state
            COLOR_BTN_SUCCESS_TEXT          = COLOR_PROC(MONOKAI_ORANGE3); // Toggle switch "ON" state tick and rounded rectangle color, FileTransfer successfully finished text: "click to open" and filename, Settings buttons like: "Show password field" text, Call/FileTransfer/Send message button icons in normal state
            COLOR_BTN_SUCCESS_BKGRND_HOVER  = COLOR_PROC(MONOKAI_GRAY4); // Same as above but for hover
            COLOR_BTN_SUCCESS_TEXT_HOVER    = COLOR_PROC(MONOKAI_ORANGE3); // Same as above but for hover

            COLOR_BTN_WARNING_BKGRND        = COLOR_PROC(MONOKAI_GRAY4); // Call button bg during an incoming call
            COLOR_BTN_WARNING_TEXT          = COLOR_MAIN_TEXT; // Call button icon color during an incoming call
            COLOR_BTN_WARNING_BKGRND_HOVER  = COLOR_PROC(MONOKAI_GRAY4); // Same as above but for hover
            COLOR_BTN_WARNING_TEXT_HOVER    = COLOR_BKGRND_MAIN; // Same as above but for hover

            COLOR_BTN_DANGER_BACKGROUND     = COLOR_PROC(MONOKAI_GRAY4); // Call button bg during outgoing call and during esablished call
            COLOR_BTN_DANGER_TEXT           = COLOR_MAIN_TEXT; // Call button icon color during outgoing call and during esablished call
            COLOR_BTN_DANGER_BKGRND_HOVER   = COLOR_PROC(MONOKAI_GRAY4); // Same as above but for hover
            COLOR_BTN_DANGER_TEXT_HOVER     = COLOR_BKGRND_MAIN; // Same as above but for hover

            COLOR_BTN_DISABLED_BKGRND       = COLOR_PROC(MONOKAI_GRAY4); // Toggle switch "OFF" state bg, FileTransfer failed or cancelled bg, call/filesend/send message buttons when contact is offline, though you can still click on send message and it will be delivered when user comes online
            COLOR_BTN_DISABLED_TEXT         = COLOR_PROC(MONOKAI_ORANGE3); // Toggle switch "OFF" state "X" and rounded rectangle, FileTransfer failed or cancelled text
            COLOR_BTN_DISABLED_BKGRND_HOVER = COLOR_PROC(MONOKAI_GRAY4); // Same as above but for hover
            COLOR_BTN_DISABLED_TRANSFER     = COLOR_BKGRND_LIST;
            COLOR_BTN_DISABLED_FORGRND      = COLOR_PROC(SOLAR_ORANGE);

            COLOR_BTN_INPROGRESS_FORGRND = COLOR_MAIN_TEXT_ACTION; // FileTransfer progress bar: transfer progress
            COLOR_BTN_INPROGRESS_BKGRND  = COLOR_PROC(MONOKAI_GRAY1); // FileTransfer progress bar: bg
            COLOR_BTN_INPROGRESS_TEXT    = COLOR_MAIN_TEXT; // FileTransfer progress bar text
            break;
        }
        case THEME_CUSTOM: {
            size_t size;
            uint8_t *themedata = utox_data_load_custom_theme(&size);
            if (!themedata) {
                return;
            }
            read_custom_theme(themedata, size);
            free(themedata);
            break;
        }
        case THEME_DEFAULT: {
            // Set above the switch.
            break;
        }
    }

    status_color[0] = COLOR_STATUS_ONLINE;
    status_color[1] = COLOR_STATUS_AWAY;
    status_color[2] = COLOR_STATUS_BUSY;
    status_color[3] = COLOR_STATUS_BUSY;
}

uint32_t *find_colour_pointer(char *color) {
    while (*color == 0 || *color == ' ' || *color == '\t') {
        ++color;
    }

    for (int l = strlen(color) - 1; l > 0; --l) {
        if (color[l] != ' ' && color[l] != '\t') {
            color[l + 1] = '\0';
            break;
        }
    }

    // Skip past "COLOR_" prefix
    if (!strncmp(color, "COLOR_", 6)) {
        color += 6;
    }

    LOG_INFO("Theme", "Color: %s" , color);

    for (int i = 0;; ++i) {
        const char *s = COLOUR_NAME_TABLE[i];

        if (!s) {
            break;
        }

        if (!strcmp(color, s)) {
            return COLOUR_POINTER_TABLE[i];
        }
    }

    return NULL;
}

static uint32_t try_parse_hex_colour(char *color, bool *error) {
    while (*color == 0 || *color == ' ' || *color == '\t') {
        color++;
    }

    for (int l = strlen(color) - 1; l > 0; --l) {
        if (color[l] != ' ' && color[l] != '\n') {
            color[++l] = '\0';

            if (l != 6) {
                *error = true;
                return 0;
            }
            break;
        }
    }

    char hex[3] = { 0 };

    memcpy(hex, color, 2);
    unsigned char red = strtol(hex, NULL, 16);
    memcpy(hex, color + 2, 2);
    unsigned char green = strtol(hex, NULL, 16);
    memcpy(hex, color + 4, 2);
    unsigned char blue = strtol(hex, NULL, 16);

    return RGB(red, green, blue);
}

static void read_custom_theme(const uint8_t *data, size_t length) {
    while (length) {
        char *line = (char *)data;
        while (*line != 0) {
            if (*line == '#') {
                *line = 0;
                break;
            }
            ++line;
            --length;
        }

        char *color = strpbrk(line, "=");

        if (!color || color == line) {
            continue;
        }

        *color++ = 0;

        uint32_t *colorp = find_colour_pointer(line);
        if (!colorp) {
            continue;
        }

        bool err = false;
        const uint32_t col = try_parse_hex_colour(color, &err);

        if (err) {
            LOG_ERR("Theme", "Error: Parsing hex color failed.");
            continue;
        } else {
            *colorp = COLOR_PROC(col);
        }
    }
}

static uint8_t *utox_data_load_custom_theme(size_t *out) {
    FILE *fp = utox_get_file("utox_theme.ini", out, UTOX_FILE_OPTS_READ);

    if (fp == NULL) {
        LOG_ERR("Theme", "Failed to open custom theme file.");
        return NULL;
    }

    uint8_t *data = calloc(1, *out + 1);
    if (data == NULL) {
        LOG_ERR("Theme", "Failed to allocate memory for custom theme.");
        fclose(fp);
        return NULL;
    }

    if (fread(data, *out, 1, fp) != 1) {
        LOG_ERR("Theme", "Could not read custom theme from file.");
        fclose(fp);
        free(data);
        return NULL;
    }
    fclose(fp);

    return data;
}

#ifndef THEME_H
#define THEME_H

#include <stdint.h>

typedef enum {
    THEME_DEFAULT,
    THEME_LIGHT,
    THEME_DARK,
    THEME_HIGHCONTRAST,
    THEME_CUSTOM,
    THEME_ZENBURN,
    THEME_SOLARIZED_LIGHT,
    THEME_SOLARIZED_DARK,
    THEME_MONOKAI,
    // TODO: THEME_XRESOURCE
} THEME;

/* Colors for drawing the backgrounds */
extern uint32_t COLOR_BKGRND_MAIN;
extern uint32_t COLOR_BKGRND_ALT;
extern uint32_t COLOR_BKGRND_AUX;
extern uint32_t COLOR_BKGRND_MENU;
extern uint32_t COLOR_BKGRND_MENU_HOVER;
extern uint32_t COLOR_BKGRND_MENU_ACTIVE;
extern uint32_t COLOR_BKGRND_LIST;
extern uint32_t COLOR_BKGRND_LIST_HOVER;

extern uint32_t COLOR_MAIN_TEXT;
extern uint32_t COLOR_MAIN_TEXT_CHAT;
extern uint32_t COLOR_MAIN_TEXT_SUBTEXT;
extern uint32_t COLOR_MAIN_TEXT_ACTION;
extern uint32_t COLOR_MAIN_TEXT_QUOTE;
extern uint32_t COLOR_MAIN_TEXT_RED;
extern uint32_t COLOR_MAIN_TEXT_URL;
extern uint32_t COLOR_MAIN_TEXT_HINT;

extern uint32_t COLOR_MSG_USER;
extern uint32_t COLOR_MSG_USER_PEND;
extern uint32_t COLOR_MSG_USER_ERROR;
extern uint32_t COLOR_MSG_CONTACT;

extern uint32_t COLOR_MENU_TEXT;
extern uint32_t COLOR_MENU_TEXT_SUBTEXT;
extern uint32_t COLOR_MENU_TEXT_ACTIVE;

extern uint32_t COLOR_LIST_TEXT;
extern uint32_t COLOR_LIST_TEXT_SUBTEXT;

extern uint32_t COLOR_AUX_EDGE_NORMAL;
extern uint32_t COLOR_AUX_EDGE_HOVER;
extern uint32_t COLOR_AUX_EDGE_ACTIVE;
extern uint32_t COLOR_AUX_TEXT;
extern uint32_t COLOR_AUX_ACTIVEOPTION_BKGRND;
extern uint32_t COLOR_AUX_ACTIVEOPTION_TEXT;

extern uint32_t COLOR_GROUP_SELF;
extern uint32_t COLOR_GROUP_PEER;
extern uint32_t COLOR_GROUP_AUDIO;
extern uint32_t COLOR_GROUP_MUTED;

extern uint32_t COLOR_SELECTION_BACKGROUND;
extern uint32_t COLOR_SELECTION_TEXT;

extern uint32_t COLOR_EDGE_NORMAL;
extern uint32_t COLOR_EDGE_ACTIVE;
extern uint32_t COLOR_EDGE_HOVER;

extern uint32_t COLOR_ACTIVEOPTION_BKGRND;
extern uint32_t COLOR_ACTIVEOPTION_TEXT;

extern uint32_t COLOR_STATUS_ONLINE;
extern uint32_t COLOR_STATUS_AWAY;

extern uint32_t COLOR_STATUS_BUSY;
extern uint32_t COLOR_BTN_SUCCESS_BKGRND;
extern uint32_t COLOR_BTN_SUCCESS_TEXT;
extern uint32_t COLOR_BTN_SUCCESS_BKGRND_HOVER;
extern uint32_t COLOR_BTN_SUCCESS_TEXT_HOVER;

extern uint32_t COLOR_BTN_WARNING_BKGRND;
extern uint32_t COLOR_BTN_WARNING_TEXT;
extern uint32_t COLOR_BTN_WARNING_BKGRND_HOVER;
extern uint32_t COLOR_BTN_WARNING_TEXT_HOVER;

extern uint32_t COLOR_BTN_DANGER_BACKGROUND;
extern uint32_t COLOR_BTN_DANGER_TEXT;
extern uint32_t COLOR_BTN_DANGER_BKGRND_HOVER;
extern uint32_t COLOR_BTN_DANGER_TEXT_HOVER;

extern uint32_t COLOR_BTN_DISABLED_BKGRND;
extern uint32_t COLOR_BTN_DISABLED_TEXT;
extern uint32_t COLOR_BTN_DISABLED_BKGRND_HOVER;
extern uint32_t COLOR_BTN_DISABLED_TRANSFER;

extern uint32_t COLOR_BTN_INPROGRESS_BKGRND;
extern uint32_t COLOR_BTN_INPROGRESS_TEXT;
extern uint32_t COLOR_BTN_DISABLED_FORGRND;
extern uint32_t COLOR_BTN_INPROGRESS_FORGRND;

void theme_load(const THEME loadtheme);

extern uint32_t status_color[4];

#endif

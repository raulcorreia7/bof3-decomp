#include "game_00.h"

#include "shared/Menu_SlidePanelLeft.h"

MATCH void Menu_SlidePanelLeft(void) {
    MenuPanelTask* task = g_MenuCurrentPanel;
    s16            val;

    MENU_SLIDE_PANEL_LEFT();
}

#include "start_08.h"

MATCH void func_801E9F04(void) {
    MenuPanelTask* panel;
    u8*            bytes;
    u16            next;

    panel        = g_MenuCurrentPanel;
    bytes        = (u8*)panel;
    next         = panel->pos.x - MENU_PANEL_STEP_X;
    panel->pos.x = next;
    if ((s16)next < (bytes[0xB] & 0x1) * 75 + 150) {
        panel->pos.x = (bytes[11] & 0x1) * 75 + 150;
        panel->state = 0;
    }
}

#include "start_08.h"

MATCH void func_801E9EAC(void) {
    MenuPanelTask* panel;
    u8*            bytes;
    u16            next;

    panel    = g_MenuCurrentPanel;
    bytes    = (u8*)panel;
    next     = panel->x + MENU_PANEL_STEP_X;
    panel->x = next;
    if ((s16)next > (bytes[0xB] & 1) * 75 + 320) {
        panel->x     = (bytes[11] & 1) * 75 + 320;
        panel->state = 0;
    }
}

#include "start_08.h"

MATCH void func_801E9F04(void) {
    MenuPanelTask* panel;
    u8*            bytes;
    u16            next;

    panel         = g_UIPanelCurrent;
    bytes         = (u8*)panel;
    next          = panel->pos.vx - MENU_PANEL_STEP_X;
    panel->pos.vx = next;
    if ((s16)next < (bytes[0xB] & 0x1) * 75 + 150) {
        panel->pos.vx = (bytes[11] & 0x1) * 75 + 150;
        panel->state  = 0;
    }
}

#include "shop_00.h"

MATCH void func_801E2D5C(void) {
    MenuPanelTask* panel;
    u8*            bytes;
    u16            next;

    panel         = g_UiPanelCurrent;
    bytes         = (u8*)panel;
    next          = panel->pos.vy + 0x10;
    panel->pos.vy = next;
    if ((s16)next > bytes[10] * 0x36 + 0x3E) {
        panel->pos.vy = bytes[10] * 54 + 62;
        panel->state  = 0;
    }
}

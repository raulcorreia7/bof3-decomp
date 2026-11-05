#include "shop_00.h"

MATCH void func_801E2D5C(void) {
    MenuPanelTask* panel;
    u8*            bytes;
    u16            next;

    panel    = g_MenuCurrentPanel;
    bytes    = (u8*)panel;
    next     = panel->y + 0x10;
    panel->y = next;
    if ((s16)next > bytes[10] * 0x36 + 0x3E) {
        panel->y     = bytes[10] * 54 + 62;
        panel->state = 0;
    }
}

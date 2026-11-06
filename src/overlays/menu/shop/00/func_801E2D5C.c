#include "shop_00.h"

MATCH void func_801E2D5C(void) {
    MenuPanelTask* panel;
    u8*            bytes;
    u16            next;

    panel        = g_MenuCurrentPanel;
    bytes        = (u8*)panel;
    next         = panel->pos.y + 0x10;
    panel->pos.y = next;
    if ((s16)next > bytes[10] * 0x36 + 0x3E) {
        panel->pos.y = bytes[10] * 54 + 62;
        panel->state = 0;
    }
}

#include "shop_00.h"

/* File-local declaration: the u16 lookup table at 0x801E5DD8 is owned by
 * this translation unit. */

MATCH void func_801E2BC4(void) {
    MenuPanelTask* panel = g_MenuCurrentPanel;
    u8*            bytes = (u8*)panel;

    Menu_DrawCursorFrame(panel->x, panel->y, D_801E5DD8[bytes[0xA]], 0x34, bytes[0xB], 6);
}

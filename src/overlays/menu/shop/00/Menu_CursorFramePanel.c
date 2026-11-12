#include "shop_00.h"

/* File-local declaration: the u16 lookup table at 0x801E5DD8 is owned by
 * this translation unit. */

/* func_801E2BC4 */
MATCH void Menu_CursorFramePanel(void) {
    MenuPanelTask* panel = g_MenuCurrentPanel;
    u8*            bytes = (u8*)panel;

    Menu_DrawCursorFrame(panel->pos.x, panel->pos.y, D_801E5DD8[bytes[0xA]], 52, bytes[0xB], 6);
}

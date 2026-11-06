#include "start_08.h"

MATCH void func_801E9D98(void) {
    MenuPanelTask* panel;
    u8*            bytes;

    panel = g_MenuCurrentPanel;
    bytes = (u8*)panel;
    Menu_DrawCursorFrame(panel->pos.x, panel->pos.y, D_801ED42C[bytes[0xA] * 2], D_801ED42E[bytes[0xA] * 2], bytes[0xB],
                         6);
}

#include "start_08.h"

/* func_801E9D98 */
MATCH void Menu_CursorFramePanel(void) {
    MenuPanelTask* panel;
    u8*            bytes;

    panel = g_UIPanelCurrent;
    bytes = (u8*)panel;
    Menu_DrawCursorFrame(panel->pos.vx, panel->pos.vy, g_MenuStartCursorFrames[bytes[0xA]].w, g_MenuStartCursorFrames[bytes[0xA]].h, bytes[0xB], 6);
}

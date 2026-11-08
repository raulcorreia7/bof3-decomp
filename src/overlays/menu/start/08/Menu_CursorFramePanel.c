#include "start_08.h"

/* func_801E9D98 */
MATCH void Menu_CursorFramePanel(void) {
    MenuPanelTask* panel;
    u8*            bytes;

    panel = g_MenuCurrentPanel;
    bytes = (u8*)panel;
    Menu_DrawCursorFrame(panel->pos.x, panel->pos.y, g_MenuStartCursorFrames[bytes[0xA]].width,
                         g_MenuStartCursorFrames[bytes[0xA]].height, bytes[0xB], 6);
}

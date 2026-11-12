#include "shop_00.h"

/* func_801E4DF4 */
MATCH void Shop_DrawCuePanel(MenuPanelTask* panel_task) {
    u8* bytes;

    bytes = (u8*)panel_task;
    UI_DrawWindow((u16)(panel_task->pos.x + 3), (u16)(panel_task->pos.y + 3), 154, 57, 0, g_WindowStyle);
    Menu_DrawPanelFrame(panel_task->pos.x, panel_task->pos.y, 18, 6);
    WinDrawCueText((panel_task->pos.x + 14), (panel_task->pos.y + 4), bytes[0xA] | 0x100);
}

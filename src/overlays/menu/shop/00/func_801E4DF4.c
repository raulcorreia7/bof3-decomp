#include "shop_00.h"

MATCH void func_801E4DF4(MenuPanelTask* panel_task) {
    u8* bytes;

    bytes = (u8*)panel_task;
    UI_DrawWindow((u16)(panel_task->x + 3), (u16)(panel_task->y + 3), 154, 57, 0, D_80144952);
    Menu_DrawPanelFrame(panel_task->x, panel_task->y, 0x12, 6);
    WinDrawCueText((panel_task->x + 14), (panel_task->y + 4), bytes[0xA] | 0x100);
}

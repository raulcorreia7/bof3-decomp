#include "start_08.h"

void Menu_DrawPanelIcon(u16 icon_x, u16 icon_y, s32 icon_u, s32 icon_v, u16 icon_clut, u8 icon_shade);

MATCH void func_801E8DB4(MenuPanelTask* task) {
    u8* table;
    u8* row;

    table = D_80144F5A;
    row   = table + task->unk_0B * 3;
    Menu_DrawCharacterWindow(task->pos.x, task->pos.y, g_CharSlot[row[task->unk_0A]], task->unk_0C, 0);
    if (GetGraphType() != 1) {
        GetGraphType();
    }
    GFX_AddDrawMode(0xF);
    Menu_DrawPanelIcon((task->pos.x + 9) & HALF_MASK, (task->pos.y + 5) & HALF_MASK, (task->unk_0A + 3) & BYTE_MASK,
                       0x1E, (GetClut(16, 480) & HALF_MASK), 128);
}

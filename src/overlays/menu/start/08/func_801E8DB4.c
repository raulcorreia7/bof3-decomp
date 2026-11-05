#include "start_08.h"

void func_801DD618(u16 icon_x, u16 icon_y, s32 icon_u, s32 icon_v, u16 icon_clut, u8 icon_shade);

MATCH void func_801E8DB4(MenuPanelTask* task) {
    u8* table;
    u8* row;

    table = D_80144F5A;
    row   = table + task->unk_0B * 3;
    Menu_DrawCharacterWindow(task->x, task->y, g_CharSlot[row[task->unk_0A]], task->unk_0C, 0);
    if (GetGraphType() != 1) {
        GetGraphType();
    }
    GFX_AddDrawMode(0xF);
    func_801DD618((task->x + 9) & HALF_MASK, (task->y + 5) & HALF_MASK, (task->unk_0A + 3) & BYTE_MASK, 0x1E,
                  (u16)(GetClut(16, 480) & HALF_MASK), 128);
}

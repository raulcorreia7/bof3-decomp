#include "area052_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F35A0(void) {
    s32 column_fixed;
    s32 column;
    s32 cell_column;
    s32 row;
    s32 row_next;
    u8  i;

    if (g_Task->pos.x.fixed != TO_COORD_HALF(0x11)) {
        return;
    }
    if (g_Task->pos.y.fixed != TO_COORD_HALF(0x29)) {
        return;
    }
    column_fixed = TO_COORD(0x11);
    column       = 0x11;
    row          = 0x29;
    i            = 0;
    do {
        Area_StoreHeight(column + i, row, 0);
        Area_SetCellCode(column + i, row, (g_Task->unk_18 >> (i * 8)) & 0xFF);
        Area_StoreHeight(column + i, row + 1, 0);
        Area_SetCellCode(column + i, row + 1, (g_Task->unk_1C >> (i * 8)) & 0xFF);
        i++;
    } while (i < 2);

    g_Task->unk_18      = 0;
    g_Task->unk_1C      = 0;
    g_Task->pos.y.fixed = TO_COORD_HALF(7);
    i                   = 0;
    column              = FIX_INT(column_fixed);
    cell_column         = FIX_INT(column_fixed);
    row                 = 7;
    row_next            = TO_COORD(row + 1);
    do {
        Area_StoreHeight(column + i, row, 0x10);
        g_Task->unk_18 |= (u8)Area_GetCellCode(i + cell_column, row) << (i * 8);
        Area_SetCellCode(column + i, row, 0x11);
        Area_StoreHeight(column + i, row + 1, 0x10);
        g_Task->unk_1C |= (u8)Area_GetCellCode(i + cell_column, FIX_INT(row_next)) << (i * 8);
        Area_SetCellCode(column + i, row + 1, 0x11);
        i++;
    } while (i < 2);
}
#else
INCLUDE_ASM(func_801F35A0);
#endif

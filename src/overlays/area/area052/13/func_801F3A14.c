#include "area052_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3A14(s32 x, s32 y) {
    s16 column;
    s16 row;

    column = FIX_INT(x);
    row    = FIX_INT(y);
    Area_StoreHeight(column, row, 0);
    Area_SetCellCode(column, row, (u8)g_Task->unk_18);
    Area_StoreHeight(column, row + 1, 0);
    Area_SetCellCode(column, row + 1, (u8)g_Task->unk_1C);
    column += 2;
    g_Task->unk_18 >>= 8;
    g_Task->unk_1C >>= 8;
    Area_StoreHeight(column, row, 0x10);
    g_Task->unk_18 |= (u8)Area_GetCellCode(column, row) << 8;
    Area_SetCellCode(column, row, 0x11);
    row += 1;
    Area_StoreHeight(column, row, 0x10);
    g_Task->unk_1C |= (u8)Area_GetCellCode(column, row) << 8;
    Area_SetCellCode(column, row, 0x11);
    g_Task->direction_08 = FACING_RIGHT;
    Area_MoveActorRoute(g_ScriptState, 3);
    g_ScriptState->unk_07 = 2;
}
#else
INCLUDE_ASM(func_801F3A14);
#endif

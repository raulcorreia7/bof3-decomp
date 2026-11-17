#include "area052_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3A14(s32 x, s32 y) {
    /* FAKE: retail shifts the x coordinate in s0 after its parameter copy. */
    FAKE_REG(s32, column, "s0");
    /* FAKE: retail shifts the y coordinate in s1 after its parameter copy. */
    FAKE_REG(s32, row, "s1");

    column = x;
    row    = y;
    /* FAKE: keep the parameter copy in s0 before the retail in-place shift. */
    FAKE_OPAQUE(column);
    /* FAKE: keep the parameter copy in s1 before the retail in-place shift. */
    FAKE_OPAQUE(row);
    column >>= 16;
    row >>= 16;
    Area_StoreHeight(column, row, 0);
    Area_SetCellCode(column, row, (u8)g_Task->unk_18);
    Area_StoreHeight(column, row + 1, 0);
    Area_SetCellCode(column, row + 1, (u8)g_Task->unk_1C);
    column = (s16)(column + 2);
    g_Task->unk_18 >>= 8;
    g_Task->unk_1C >>= 8;
    Area_StoreHeight(column, row, 0x10);
    g_Task->unk_18 |= (u8)Area_GetCellCode(column, row) << 8;
    Area_SetCellCode(column, row, 0x11);
    row = (s16)(row + 1);
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

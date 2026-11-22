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
    Area_HeightSet(column, row, 0);
    Area_CellSetCode(column, row, (u8)TASK(Actor)->unk_18);
    Area_HeightSet(column, row + 1, 0);
    Area_CellSetCode(column, row + 1, (u8)TASK(Actor)->unk_1C);
    column = (s16)(column + 2);
    TASK(Actor)->unk_18 >>= 8;
    TASK(Actor)->unk_1C >>= 8;
    Area_HeightSet(column, row, 0x10);
    TASK(Actor)->unk_18 |= (u8)Area_CellGetCode(column, row) << 8;
    Area_CellSetCode(column, row, 0x11);
    row = (s16)(row + 1);
    Area_HeightSet(column, row, 0x10);
    TASK(Actor)->unk_1C |= (u8)Area_CellGetCode(column, row) << 8;
    Area_CellSetCode(column, row, 0x11);
    TASK(Actor)->direction = FACING_RIGHT;
    Area_MoveActorRoute(g_ScriptState, 3);
    g_ScriptState->steps = 2;
}
#else
INCLUDE_ASM(func_801F3A14);
#endif

#include "area052_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3A14(s32 x, s32 y) {
    s32 column;
    s32 row;

    column = x;
    row    = y;
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

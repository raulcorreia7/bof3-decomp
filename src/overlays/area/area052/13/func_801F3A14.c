#include "area052_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3A14(s32 x, s32 y) {
    s16 column;
    s16 row;

    column = FIX_INT(x);
    row    = FIX_INT(y);
    Area_HeightSet(column, row, 0);
    Area_CellSetCode(column, row, (u8)SELF(Actor)->unk_18);
    Area_HeightSet(column, row + 1, 0);
    Area_CellSetCode(column, row + 1, (u8)SELF(Actor)->unk_1C);
    column += 2;
    SELF(Actor)->unk_18 >>= 8;
    SELF(Actor)->unk_1C >>= 8;
    Area_HeightSet(column, row, 0x10);
    SELF(Actor)->unk_18 |= (u8)Area_CellGetCode(column, row) << 8;
    Area_CellSetCode(column, row, 0x11);
    row++;
    Area_HeightSet(column, row, 0x10);
    SELF(Actor)->unk_1C |= (u8)Area_CellGetCode(column, row) << 8;
    Area_CellSetCode(column, row, 0x11);
    SELF(Actor)->direction = FACING_RIGHT;
    Area_MoveActorRoute(g_ScriptState, 3);
    g_ScriptState->steps = 2;
}
#else
INCLUDE_ASM(func_801F3A14);
#endif

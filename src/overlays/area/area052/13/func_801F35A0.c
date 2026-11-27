#include "area052_13.h"

MATCH void func_801F35A0(void) {
    s32 column_fixed;
    s32 initial_column;
    s32 column;
    s32 cell_column;
    s16 row;
    s32 i;
    u8  read_index;

    if (SELF(Actor)->pos.x.fixed != TO_COORD_HALF(0x11)) {
        return;
    }
    if (SELF(Actor)->pos.y.fixed != TO_COORD_HALF(0x29)) {
        return;
    }
    column_fixed   = TO_COORD(0x11);
    i              = 0;
    initial_column = 0x11;
    row            = 0x29;
    do {
        Area_HeightSet(initial_column + (i & BYTE_MASK), row, 0);
        Area_CellSetCode(initial_column + (i & BYTE_MASK), row, (SELF(Actor)->unk_18 >> ((i & BYTE_MASK) * 8)) & 0xFF);
        Area_HeightSet(initial_column + (i & BYTE_MASK), row + 1, 0);
        Area_CellSetCode(initial_column + (i & BYTE_MASK), row + 1, (SELF(Actor)->unk_1C >> ((i & BYTE_MASK) * 8)) & 0xFF);
        i++;
    } while ((u32)(i & BYTE_MASK) < 2U);

    SELF(Actor)->unk_18      = 0;
    SELF(Actor)->unk_1C      = 0;
    SELF(Actor)->pos.y.fixed = TO_COORD_HALF(7);
    i                        = 0;
    column                   = FIX_INT(column_fixed);
    cell_column              = FIX_INT(column_fixed);
    row                      = 7;

    do {
        Area_HeightSet(column + (i & BYTE_MASK), row, 0x10);
        read_index = i;
        SELF(Actor)->unk_18 |= (u8)Area_CellGetCode(read_index + cell_column, row) << ((i & BYTE_MASK) * 8);
        Area_CellSetCode(column + (i & BYTE_MASK), row, 0x11);
        Area_HeightSet(column + (i & BYTE_MASK), row + 1, 0x10);
        read_index = i;
        SELF(Actor)->unk_1C |= (u8)Area_CellGetCode(read_index + cell_column, (s16)(row + 1)) << ((i & BYTE_MASK) * 8);
        Area_CellSetCode(column + (i & BYTE_MASK), row + 1, 0x11);
        i++;
    } while ((u32)(i & BYTE_MASK) < 2U);
}

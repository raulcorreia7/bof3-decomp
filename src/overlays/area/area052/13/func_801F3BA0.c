#include "area052_13.h"

MATCH void func_801F3BA0(s32 x, s32 y) {
    s32 column;
    s32 row;
    s32 row_integer;

    row_integer = FIX_INT(y);
    column      = FIX_INT(x) + 1;
    row         = row_integer;
    Area_HeightSet(column, row, 0);
    func_801A4BC0(column, row, (u8)(SELF(Actor)->unk_18 >> 8));
    row++;
    Area_HeightSet(column, row, 0);
    func_801A4BC0(column, row, (u8)(SELF(Actor)->unk_1C >> 8));
    SELF(Actor)->unk_18 <<= 8;
    SELF(Actor)->unk_1C <<= 8;
}

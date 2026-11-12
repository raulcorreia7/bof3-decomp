#include "area052_13.h"

MATCH void func_801F3C4C(s32 x, s32 y) {
    s32 column;
    s32 row;
    u8  i;

    i      = 0;
    column = FIX_INT(x);
    row    = FIX_INT(y);
    do {
        Area_StoreHeight(column + i, row, 0);
        func_801A4BC0(column + i, row, (g_Task->unk_18 >> (i * 8)) & 0xFF);
        Area_StoreHeight(column + i, row + 1, 0);
        func_801A4BC0(column + i, row + 1, (g_Task->unk_1C >> (i * 8)) & 0xFF);
        i++;
    } while (i < 2);
}

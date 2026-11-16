#include "area052_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3BA0(s32 x, s32 y) {
    s32 column;
    s32 row;

    column = FIX_INT(x) + 1;
    row    = FIX_INT(y);
    Area_StoreHeight(column, row, 0);
    func_801A4BC0(column, row, (u8)(g_Task->unk_18 >> 8));
    row++;
    Area_StoreHeight(column, row, 0);
    func_801A4BC0(column, row, (u8)(g_Task->unk_1C >> 8));
    g_Task->unk_18 <<= 8;
    g_Task->unk_1C <<= 8;
}
#else
INCLUDE_ASM(func_801F3BA0);
#endif

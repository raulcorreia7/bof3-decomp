#include "area135_14.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F5F28(void) {
    s32 x;
    s32 y;
    s32 right_x;
    s32 row1;
    s32 row2;
    s32 i;
    u8  j;

    x       = g_Task->pos.x.part.integer;
    y       = g_Task->pos.y.part.integer;
    right_x = (x + 1) << 16;
    i       = 0;
    do {
        j    = i;
        row1 = (s16)(y + j);
        Area_StoreHeight(x, row1, 0);
        row2 = (s16)(y + j);
        i++;
        Area_SetCellCode(x, row1, (u8)(g_Task->gravity >> (j * 8)));
        Area_StoreHeight(right_x >> 16, row2, 0);
        Area_SetCellCode(right_x >> 16, row2, (u8)(g_Task->gravity >> ((j + 2) * 8)));
    } while ((u8)i < 2);
}
#else
INCLUDE_ASM(func_801F5F28);
#endif

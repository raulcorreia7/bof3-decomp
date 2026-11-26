#include "area170_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3994(void) {
    u8*         bundle;
    u8*         cell_base;
    u32*        cell;
    volatile u8 hidden;
    s32         row;
    s32         col;
    s32         k;
    u8          sum;
    s32         index;
    s32         wrapped;
    s32         cell_index;
    s32         cell_id;
    s32         width;

    hidden = SYS_TestFlag(g_SceneEventFlags, 0x7E) == 0;
    row    = 0;
    bundle = MEM_PTR(u8, MAP_BUNDLE_BASE);
    do {
        col = 0;
        do {
            sum = 0;
            if (hidden != 0) {
                for (k = 0; (u8)k < 3; k++) {
                    index   = D_801F5990[(u8)k] + col;
                    wrapped = index;
                    if ((u8)wrapped >= 9) {
                        wrapped = index - 9;
                    }
                    sum += (u8)D_801F58D0[(u8)k][(u8)row][(u8)wrapped];
                }
                if ((u8)sum != 0) {
                    sum = 1;
                }
            }
            func_801A4BC0((u8)col + 0x16, (u8)row + 0x8E, D_801F584C[(u8)row][(u8)col] * (u8)sum);
            width      = *bundle;
            cell_base  = bundle + ((width * D_80104001 + 1) / 2) * 4 + D_80104002 * 4;
            cell_index = LOHU(D_8010402C[D_80104002 * 4 + ((u8)row + 0x8E) * width * 2 + (u8)col * 2]);
            cell       = (u32*)(cell_base + cell_index * 4);
            *cell      = *cell & ~0xFF;
            *cell |= D_801F57CC[sum][(u8)row][(u8)col];
            cell_id = Area_CellGetId((u8)col + 0x16, (u8)row + 0x8E);
            if (cell_id != 0) {
                Area_ApplyTileToQuad(*cell, &g_AreaCellPrims[cell_id * 80], 2);
            }
            col++;
        } while ((u8)col < 9);
        row++;
    } while ((u8)row < 7);
}
#else
INCLUDE_ASM(func_801F3994);
#endif

#include "area170_13.h"

MATCH void func_801F3994(void) {
    u32* cell;
    u8   hidden;
    s32  row;
    s32  col;
    s32  k;
    u8   sum;
    s32  index;
    u8   wrapped;
    s32  cell_id;

    hidden = SYS_TestFlag(g_SceneEventFlags, 0x7E) == 0;
    row    = 0;
    do {
        col = 0;
        do {
            sum = 0;
            if (hidden != 0) {
                for (k = 0; (u8)k < 3; k++) {
                    index   = D_801F5990[(u8)k] + col;
                    wrapped = index;
                    if (wrapped >= 9) {
                        wrapped = index - 9;
                    }
                    sum += (u8)D_801F58D0[(u8)k][(u8)row][wrapped];
                }
                if ((u8)sum != 0) {
                    sum = 1;
                }
            }
            func_801A4BC0((u8)col + 0x16, (u8)row + 0x8E, D_801F584C[(u8)row][(u8)col] * (u8)sum);
            cell  = &AREA_MAP_TILES[AREA_MAP_GRID_ROW((u8)row + 0x8E)[(u8)col + 0x16]];
            *cell = *cell & ~0xFF;
            *cell |= D_801F57CC[sum][(u8)row][(u8)col];
            cell_id = Area_CellGetId((u8)col + 0x16, (u8)row + 0x8E);
            if (cell_id != 0) {
                Area_ApplyTileToQuad(*cell, &g_AreaCellPrims[cell_id][0], 2);
            }
            col++;
        } while ((u8)col < 9);
        row++;
    } while ((u8)row < 7);
}

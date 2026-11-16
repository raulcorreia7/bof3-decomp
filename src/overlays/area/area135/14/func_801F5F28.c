#include "area135_14.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F5F28(void) {
    Coord column_plus_one;
    s32   column;
    s32   row;
    s32   cell_base_row;
    s16   height_row;
    s32   cell_row;
    s32   i;
    s32   byte_index;

    column                = COORD_INT(g_Task->pos.x);
    row                   = COORD_INT(g_Task->pos.y);
    cell_base_row         = row;
    column_plus_one.fixed = TO_COORD(column + 1);
    i                     = 0;
    do {
        height_row = cell_base_row + (u8)i;
        Area_StoreHeight(column, height_row, 0);
        byte_index = (u8)i;
        cell_row   = row + byte_index;
        Area_SetCellCode(column, cell_row, (u8)(g_Task->gravity >> (byte_index * 8)));
        i++;
        Area_StoreHeight(COORD_INT(column_plus_one), height_row, 0);
        byte_index += 2;
        Area_SetCellCode(column + 1, cell_row, (u8)(g_Task->gravity >> (byte_index * 8)));
    } while (i < 2);
}
#else
INCLUDE_ASM(func_801F5F28);
#endif

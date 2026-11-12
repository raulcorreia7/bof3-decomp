#include "start_08.h"

extern void func_801E2E90(s32 x, s32 y, s32 row_index);

MATCH void func_801E2D84(s16 x, s32 y) {
    u8   data[6];
    u16* flag_table;
    s32  row_y;
    s32  i;

    memcpy(data, D_801D0E20, sizeof(data));
    Menu_DrawWindowFrame(x, y, 12, 15);
    i          = 0;
    row_y      = y + 6;
    flag_table = g_InputMasks;
    do {
        u8  cell;
        s32 cell_y;

        cell   = i;
        cell_y = (row_y + cell * 0x12) & HALF_MASK;
        func_801E2E90((u16)(x + 5), cell_y, cell);
        func_801E30FC((x + 0x44), cell_y, flag_table[data[cell]]);
        i += 1;
    } while ((i & BYTE_MASK) < 6U);
}

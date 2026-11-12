/* The cell-grid border of the commu overlays: the cell function draws one 8-pitch row along the top
 * edge, one 8-pitch column down the left edge and the two closing corners. The member passes its cell
 * function, the bottom gap, the column and row counts and the row pitch, and declares `s16 x, s16 y`,
 * `s32 i` and `s32 offset`.
 * Members: commu01/07 func_801D273C and func_801D3594, commu02/08 func_801D7EF0 and func_801D81A4. */
#define COMMU_DRAW_CELL_GRID(CELL, Y_GAP, COLUMNS, ROWS, Y_PITCH)   \
    CELL(x, y, 6);                                                  \
    for (i = 0; i < (COLUMNS); i++) {                               \
        offset = i * 8 + 8;                                         \
        CELL((s16)(x + offset), y, 7);                              \
        CELL((s16)(x + offset), (s16)(y + (Y_GAP)), 0xC);           \
    }                                                               \
    CELL((s16)(x + (COLUMNS) * 8 + 8), y, 8);                       \
    for (i = 0; i < (ROWS); i++) {                                  \
        offset = i * (Y_PITCH) + 8;                                 \
        CELL(x, (s16)(y + offset), 9);                              \
        CELL((s16)(x + (COLUMNS) * 8 + 8), (s16)(y + offset), 0xA); \
    }                                                               \
    CELL(x, (s16)(y + (Y_GAP)), 0xB);                               \
    CELL((s16)(x + (COLUMNS) * 8 + 8), (s16)(y + (Y_GAP)), 0xD)

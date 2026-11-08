#include "engine/slus/slus.h"

MATCH void Area_IndexCells(void) {
    /* FAKE: unused frame, 8 bytes. */
    FAKE_STACK_PADS(u8, 8);
    s16* table_base;
    s16* value;
    s16* cell;
    u8*  record;
    u8*  table;
    s32  origin_x;
    s32  origin_y;
    s32  row_offset;
    s32  column_offset;
    s32  row;
    s32  column;
    s32  dy;
    u32  base;
    u16  record_index;

    table_base = (s16*)&g_AreaCellGrid;
    for (row = 0; row < AREA_CELL_GRID_ROWS; row++) {
        column = AREA_CELL_GRID_COLS - 1;
        value  = table_base + row * AREA_CELL_GRID_COLS + AREA_CELL_GRID_COLS - 1;
        do {
            *value = 0;
            column--;
            value--;
        } while (column >= 0);
    }

    record = (u8*)MAP_BUNDLE_BASE + g_AreaMapBundle.record_region_24 * 4;
    if (*(u32*)record != 0) {
        table         = (u8*)&g_AreaCellGrid;
        origin_x      = g_AreaTileOriginX;
        origin_y      = g_AreaTileOriginY;
        row_offset    = g_AreaGridRowCursor;
        column_offset = g_AreaGridColCursor;
        do {
            /* FAKE: Reuse v1 for the x delta, difference and adjusted column. */
            FAKE_REG(s32, difference, "v1");
            s32 raw_row;
            difference = record[1] - origin_x;
            dy         = record[0] - origin_y;
            raw_row    = difference + dy;
            difference = difference - dy;
            if (((u32)raw_row < AREA_CELL_GRID_ROWS) && ((u32)difference < AREA_CELL_GRID_ROWS)) {
                {
                    s32 row_delta;
                    /* FAKE: Pin wrapped row to a0. */
                    FAKE_REG(s32, table_row, "a0");
                    row_delta = raw_row + 1;
                    raw_row   = row_offset + row_delta;
                    if (raw_row < AREA_CELL_GRID_ROWS) {
                        table_row = raw_row;
                    } else {
                        table_row = raw_row - AREA_CELL_GRID_ROWS;
                    }
                    raw_row = table_row;
                }
                /* FAKE: Preserve row scheduling. */
                FAKE_BARRIER();
                {
                    /* FAKE: Pin column step to v0 for the retail calculation. */
                    FAKE_REG(s32, column_delta, "v0");
                    /* FAKE: Pin wrapped column to a0 after row use ends. */
                    FAKE_REG(s32, table_column, "a0");
                    column_delta = difference / 2 + 1;
                    difference   = column_offset + column_delta;
                    if (difference < AREA_CELL_GRID_COLS) {
                        table_column = difference;
                    } else {
                        table_column = difference - AREA_CELL_GRID_COLS;
                    }
                    difference = 0x7FEFC000;
                    base       = raw_row * 0x38 + (u32)table;
                    cell       = (s16*)((table_column * 2) + base);
                    /* FAKE: Preserve wrapped-index order. */
                    FAKE_BARRIER();
                    record_index = g_AreaMapBundle.record_region_24;
                    difference += record;
                    difference -= record_index * 4;
                    difference = (difference >> 2) + 1;
                    *cell      = difference;
                }
            }
            record += *(u16*)(record + 2) * 4;
        } while (*(u32*)record != 0);
    }
}

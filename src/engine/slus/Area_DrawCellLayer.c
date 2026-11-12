#include "engine/slus/slus.h"

/* rotates the row/column cursors, walks a segment of the g_AreaCellGrid cell table and dispatches every
 * populated cell's record list through the D_8017F668 callbacks; this entry's packet first gets its low 24 bits
 * replaced by the D_80142CC0 colour.
 */
MATCH void Area_DrawCellLayer(s32 layer) {
    /* FAKE: unused frame, 8 bytes. */
    FAKE_STACK_PADS(u8, 8);
    u32* packet;
    u32  entry;
    s32  col;
    /* FAKE: Retail keeps the column offset in s6 across the callback calls. */
    FAKE_REG(s32, col_offset, "s6");
    u16* row_base;
    u8*  base;
    u8*  record;
    u8*  end;
    s32  offset;
    s32  next;
    s32  row;
    s32  index;
    s32  cell;
    s32  cell_x;
    s32  cell_y;
    u32  header;

    offset = g_FrameBufferIndex * 8 + layer * 0x30;
    entry  = *(u32*)(D_80142CC0 + offset);
    if (entry != 0) {
        packet     = (u32*)D_801459E8;
        *packet    = (*packet & 0xFF000000) | (entry & 0xFFFFFF);
        D_801459E8 = *(u32*)(D_80142CC4 + offset);
    }

    next = layer + 1;
    row  = g_AreaGridRowCursor + next;
    row  = (row >= AREA_CELL_GRID_ROWS) ? (row - AREA_CELL_GRID_ROWS) : row;

    col_offset = D_80149341;
    if (g_GameRequestFlags & 0x1) {
        col_offset = (col_offset < 2) ? 0 : col_offset - 2;
    }

    col = row ^ 0x1;
    col &= 1;
    col += g_AreaGridColCursor + col_offset;
    col = (col >= AREA_CELL_GRID_COLS) ? (col - AREA_CELL_GRID_COLS) : col;

    index = 0;
    if ((AREA_CELL_GRID_COLS - col_offset * 2) > 0) {
        base     = (u8*)&g_AreaCellGrid;
        row_base = (u16*)(base + row * AREA_CELL_GRID_COLS * 2);
        do {
            col  = (col == AREA_CELL_GRID_COLS - 1) ? 0 : col + 1;
            cell = row_base[col];
            if (cell != 0) {
                record = (u8*)MAP_BUNDLE_BASE + g_AreaMapBundle.record_region_24 * 4 + cell * 4;
                header = *(u32*)(record - 4);
                end    = record + ((header >> 16) * 4 - 4);
                cell_x = (header >> 8) & BYTE_MASK;
                cell_y = header & BYTE_MASK;
                while (record != end) {
                    D_8017F668[record[3]](record, cell_x, cell_y);
                    record += record[2] * 4;
                }
            }
            index++;
        } while (index < (AREA_CELL_GRID_COLS - col_offset * 2));
    }
}

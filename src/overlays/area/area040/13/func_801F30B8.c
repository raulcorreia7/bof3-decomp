#include "area040_13.h"

MATCH s32 func_801F30B8(s32 x, s32 y) {
    s16  dx;
    s16  dy;
    s32  row;
    s32  col;
    s32  one;
    s32  next;
    u16  cell;
    u8*  map;
    u8*  entry;
    u8*  end;
    s32  word;
    s32  value;
    s32* object;

    dx  = x - g_AreaTileOriginX;
    dy  = y - g_AreaTileOriginY;
    row = dx + dy;
    if (((u32)row) >= AREA_CELL_GRID_ROWS) {
        return 0;
    }
    next = row + 1;
    row  = g_AreaGridRowCursor + next;
    row  = (row >= AREA_CELL_GRID_ROWS) ? (row - AREA_CELL_GRID_ROWS) : (row);
    col  = dx - dy;
    one  = 1;
    if (((u32)col) >= AREA_CELL_GRID_ROWS) {
        return 0;
    }
    col  = g_AreaGridColCursor + ((col / 2) + one);
    col  = (col >= AREA_CELL_GRID_COLS) ? (col - AREA_CELL_GRID_COLS) : (col);
    cell = g_AreaCellGrid[row][col];
    if (cell == 0) {
        return 0;
    }
    map   = (u8*)MAP_BUNDLE_BASE;
    entry = (u8*)(g_AreaMapBundle.record_region_24 * 4 + (s32)(map + cell * 4));
    end   = entry + ((MEM(u16, entry - 2) * 4) - 4);
    if (entry != end) {
        do {
            word = MEM(s32, entry);
            if ((word & BUNDLE_COMMAND_MASK) == BUNDLE_COMMAND(0x23) || (word & BUNDLE_COMMAND_MASK) == BUNDLE_COMMAND(0x24) || (word & BUNDLE_COMMAND_MASK) == BUNDLE_COMMAND(0x25)) {
                object = MEM_PTR(s32, (*MEM_PTR(u16, MAP_BUNDLE_BASE + 0x28) * 4) + MAP_BUNDLE_BASE + MEM(u16, entry) * 4);
                value  = *object;
                if ((value & 0xF000) == 0x8000) {
                    return value & 1;
                }
            }
            entry += entry[2] * 4;
        } while (entry != end);
    }
    return 0;
}

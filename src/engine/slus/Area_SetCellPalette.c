#include "engine/slus/slus.h"

/* probes the bundle cell grid: the (x, y) delta becomes a row/column pair (both outside 0x38 reject with
 * 0), rotated by the cursor offsets g_AreaGridRowCursor/g_AreaGridColCursor, reads the cell halfword at g_AreaCellGrid and rewrites every
 * 0x23 command of its primitive list to 0x24, setting the low flag bit of its palette record.
 */
MATCH s32 Area_SetCellPalette(s32 x, s32 y) {
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
    s32  command;
    s32  value;
    s32  changed;
    s32* object;
    dx      = x - g_AreaTileOriginX;
    dy      = y - g_AreaTileOriginY;
    changed = 0;
    row     = dx + dy;
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
    end   = entry + (((*((u16*)(entry - 2))) * 4) - 4);
    if (entry != end) {
        do {
            word = *((s32*)entry);
            if ((word & 0xFF000000) == 0x23000000) {
                command        = (word & 0xFFFFFF) | 0x24000000;
                *((s32*)entry) = command;
                /* kept: the folded constant address keeps retail's own base load; the member form shares the register of map. */
                object =
                    (s32*)((*MEM_PTR(u16, (MAP_BUNDLE_BASE + 0x28)) * 4) + MAP_BUNDLE_BASE + (command & HALF_MASK) * 4);
                value = *object;
                if ((value & 0xF001) == 0x8000) {
                    *object = value | 1;
                    changed = 1;
                }
            }
            entry += entry[2] * 4;
        } while (entry != end);
    }
    return changed;
}

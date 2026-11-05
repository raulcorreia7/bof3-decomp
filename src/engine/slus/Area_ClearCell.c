#include "engine/slus/slus.h"

/* clears the cell byte in the map's byte-code table, maps the cell
 * through the grid table g_AreaCellGrid, then walks the cell's primitive list and
 * rewrites the render code of every quad command to 0x30.
 */
MATCH void Area_ClearCell(s32 x, s32 y) {
    AreaMapBundle* map;
    u8*            prim;
    u8*            end;
    s16            dx;
    s16            dy;
    s32            row;
    s32            col;
    s32            next;
    s32            one;
    u16            cell;

    map                                                            = (AreaMapBundle*)MAP_BUNDLE_BASE;
    *(u8*)((u8*)g_AreaCellCodes + (s16)y * map->width_00 + (s16)x) = 0;
    dx                                                             = (s16)(x - ((u16)g_AreaTileOriginX - 1));
    dy                                                             = (s16)(y - (u16)g_AreaTileOriginY);
    row                                                            = dx + dy;
    if ((u32)row >= AREA_CELL_GRID_ROWS)
        return;
    next = row + 1;
    row  = g_AreaGridRowCursor + next;
    row  = (row >= AREA_CELL_GRID_ROWS) ? (row - AREA_CELL_GRID_ROWS) : row;
    col  = dx - dy;
    if ((u32)col >= AREA_CELL_GRID_ROWS)
        return;
    one  = 1;
    col  = g_AreaGridColCursor + (col / 2 + one);
    col  = (col >= AREA_CELL_GRID_COLS) ? (col - AREA_CELL_GRID_COLS) : col;
    cell = g_AreaCellGrid[row][col];
    if (cell != 0) {
        prim = (u8*)(g_AreaMapBundle.record_region_24 * 4 + (s32)((u8*)map + cell * 4));
        end  = prim + (*(u16*)(prim - 2) * 4 - 4);
        while (prim != end) {
            if ((*(u32*)prim & 0xFF000000) == 0x03000000 || (*(u32*)prim & 0xFF000000) == 0x09000000 ||
                (*(u32*)prim & 0xFF000000) == 0x27000000) {
                *(u32*)prim = (*(u32*)prim & 0xFFFFFF) | 0x30000000;
            }
            prim += *(u8*)(prim + 2) * 4;
        }
    }
}

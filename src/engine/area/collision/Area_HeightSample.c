#include "engine/slus/slus.h"

/* samples the bundle's four-corner cell records and height bytes at the 16.16 point (x, y): the half-cell
 * bits pick the corner formula, g_AreaHeightOffsetEnabled scales the height byte (cleared by the caller), and the result is the
 * larger diagonal sum * 16 or, with both half-cell bits, the largest corner * 32, as s16; outside the grid it returns
 * 0.
 */
/* The height of corner `n` (0-3) of one map cell word: a byte each, read from the whole word. */
#define AREA_CELL_CORNER(cell, n) ((cell) >> ((n) * 8))

MATCH s16 Area_HeightSample(s32 x, s32 y) {
    s8   corner[4];
    s32  lower;
    s32  column;
    s32  upper;
    s32  row_start;
    s32  lift;
    s32  stride;
    s8*  heights_below;
    u32* cell_below;
    u32* cell_next;
    u32  corners;
    s32  width;
    s32  whole_x;
    s32  whole_y;
    u32  outside;
    s32  column_offset;
    s32  row_cells;
    s32  next;
    s32  next_offset;
    s8*  heights;
    u32* cell;
    u8*  bundle;

    /* kept: the bundle address is a constant in a register, not the g_AreaMapBundle symbol. */
    bundle  = (u8*)MAP_BUNDLE_BASE;
    width   = *bundle;
    whole_x = x >> 16;
    whole_y = y >> 16;
    outside = (u32)whole_x >> 31;
    outside |= whole_x >= width;
    outside |= (u32)whole_y >> 31;
    outside |= whole_y >= g_AreaMapBundle.height;
    if (outside != 0) {
        return 0;
    }
    y &= ~0x7FFF;
    row_start = (y >> 16) * width;
    x &= ~0x7FFF;
    column        = x >> 16;
    column_offset = column * 4;
    row_cells     = row_start * 4 + (MAP_BUNDLE_BASE + 0x30);
    cell          = (u32*)(column_offset + row_cells);
    heights       = (s8*)(g_AreaMapBundle.height_offset * 4 + (s32)(column + bundle)) + row_start;
    if (!((x | y) & HALF_MASK)) {
        lift    = heights[0] * g_AreaHeightOffsetEnabled;
        corners = cell[0];
        return (s16)(((s8)AREA_CELL_CORNER(corners, 1) + lift + (s8)AREA_CELL_CORNER(corners, 2) + lift) * 16);
    }
    stride        = width * 4;
    cell_below    = (u32*)((u8*)cell + stride);
    heights_below = heights + width;
    if ((u16)x != (u16)y) {
        if ((u16)x != 0) {
            corner[0] = AREA_CELL_CORNER(cell[0], 1) + heights[0] * g_AreaHeightOffsetEnabled;
            corner[1] = AREA_CELL_CORNER(cell[0], 3) + heights[0] * g_AreaHeightOffsetEnabled;
            corner[2] = AREA_CELL_CORNER(cell[1], 0) + heights[1] * g_AreaHeightOffsetEnabled;
            corner[3] = AREA_CELL_CORNER(cell[1], 2) + heights[1] * g_AreaHeightOffsetEnabled;
        } else {
            corner[0] = AREA_CELL_CORNER(cell[0], 2) + heights[0] * g_AreaHeightOffsetEnabled;
            corner[1] = AREA_CELL_CORNER(cell[0], 3) + heights[0] * g_AreaHeightOffsetEnabled;
            corner[2] = AREA_CELL_CORNER(*cell_below, 0) + *heights_below * g_AreaHeightOffsetEnabled;
            corner[3] = (u16)AREA_CELL_CORNER(*cell_below, 1) + *heights_below * g_AreaHeightOffsetEnabled;
        }
        upper = corner[0] + corner[1];
        lower = corner[2] + corner[3];
        if (lower < upper) {
            return upper * 16;
        }
        return lower * 16;
    }
    corner[0]   = AREA_CELL_CORNER(cell[0], 3) + heights[0] * g_AreaHeightOffsetEnabled;
    corner[1]   = AREA_CELL_CORNER(cell[1], 2) + heights[1] * g_AreaHeightOffsetEnabled;
    next_offset = stride + 4;
    next        = width + 1;
    cell_next   = (u32*)((u8*)cell + next_offset);
    corner[2]   = AREA_CELL_CORNER(*cell_next, 0) + heights[next] * g_AreaHeightOffsetEnabled;
    corner[3]   = AREA_CELL_CORNER(*cell_below, 1) + *heights_below * g_AreaHeightOffsetEnabled;
    if ((corner[0] >= corner[1]) & (corner[0] >= corner[2]) & (corner[0] >= corner[3])) {
        return corner[0] << 5;
    }
    if ((corner[1] >= corner[2]) & (corner[1] >= corner[3])) {
        return corner[1] << 5;
    }
    if (corner[2] < corner[3]) {
        return corner[3] << 5;
    }
    return corner[2] << 5;
}

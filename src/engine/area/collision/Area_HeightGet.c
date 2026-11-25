#include "engine/slus/slus.h"

#ifdef NON_MATCHING
/* The height of corner `n` (0-3) of one map cell word: a byte each, read from the whole word. */
#define AREA_CELL_CORNER(cell, n) ((cell) >> ((n) * 8))

/* The height step at the 16.16 point (x, y) for one facing: 0 off the grid, the corner rise on a
 * half-cell edge, else the slope between the corners `mode` picks; byte 0 of the scratchpad says if it is one. */
NON_MATCHING s32 Area_HeightGet(s32 x, s32 y, u8 mode) {
    s8   corner[4];
    s8   first;
    s8   second;
    s8   third;
    s8   fourth;
    s32  high;
    u8   top;
    s32  upper;
    s32  lower;
    s32  low;
    s32  diff;
    s32  row_start;
    s32  next;
    s32  next_offset;
    u32* cell_next;
    s32  column;
    s32  column_offset;
    s32  row_cells;
    s32  stride;
    s8*  heights_below;
    u32* cell_below;
    u32  corners;
    s32  lift;
    s32  width;
    s32  whole_x;
    s32  whole_y;
    u32  outside;
    u32  side;
    u32  facing;
    u32  turn;
    s8*  heights;
    u32* cell;
    u8*  bundle;

    bundle  = (u8*)MAP_BUNDLE_BASE;
    width   = *bundle;
    whole_x = x >> 16;
    whole_y = y >> 16;
    outside = (u32)whole_x >> 31;
    outside |= whole_x >= width;
    outside |= (u32)whole_y >> 31;
    outside |= whole_y >= g_AreaMapBundle.height;
    if (outside != 0) {
        g_ScratchPad.cells.bytes[0] = 0;
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
        g_ScratchPad.cells.bytes[0] = 0;
        lift                        = heights[0] * g_AreaHeightOffsetEnabled;
        corners                     = cell[0];
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
            corner[3] = AREA_CELL_CORNER(*cell_below, 1) + *heights_below * g_AreaHeightOffsetEnabled;
        }
        if ((corner[0] == corner[2]) & (corner[1] == corner[3])) {
            g_ScratchPad.cells.bytes[0] = 0;
            return (s16)((corner[0] + corner[1]) * 16);
        }
        g_ScratchPad.cells.bytes[0] = 1;
        lower                       = corner[2] + corner[3];
        upper                       = corner[0] + corner[1];
        diff                        = upper - lower;
        return (s16)(ABS(diff) * 16);
    }
    corner[0] = first = AREA_CELL_CORNER(cell[0], 3) + heights[0] * g_AreaHeightOffsetEnabled;
    corner[1] = second = AREA_CELL_CORNER(cell[1], 2) + heights[1] * g_AreaHeightOffsetEnabled;
    next_offset        = stride + 4;
    next               = width + 1;
    cell_next          = (u32*)((u8*)cell + next_offset);
    corner[2] = third = AREA_CELL_CORNER(*cell_next, 0) + heights[next] * g_AreaHeightOffsetEnabled;
    corner[3] = fourth = AREA_CELL_CORNER(*cell_below, 1) + *heights_below * g_AreaHeightOffsetEnabled;
    if ((first == second) & (first == third) & (first == fourth)) {
        g_ScratchPad.cells.bytes[0] = 0;
        return (s16)(first << 5);
    }
    g_ScratchPad.cells.bytes[0] = 1;
    turn                        = mode;
    if (mode & 1) {
        side = turn >> 1;
        top  = corner[side];
        if (corner[side] < corner[(side + 1) & 3]) {
            top = corner[(side + 1) & 3];
        }
        diff = (s8)top - corner[(side + 2) & 3];
    } else {
        facing = turn >> 1;
        diff   = corner[facing] - corner[(facing + 2) & 3];
    }
    return (s16)(ABS(diff) * 32);
}
#else
INCLUDE_ASM(Area_HeightGet);
#endif

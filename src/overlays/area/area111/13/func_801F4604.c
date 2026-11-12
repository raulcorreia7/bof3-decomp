#include "area111_13.h"

MATCH void func_801F4604(s32 cell_x, s32 cell_y, s32 tile_value) {
    s32 y;
    s32 y_bottom;
    s32 x;
    s32 x_right;
    s32 value;
    s32 y_top;
    s32 x_left;

    x      = (cell_x << 0x10) >> 0xF;
    x_left = x + 0xB;
    y      = (cell_y << 0x10) >> 0xF;
    y_top  = y + 0xB1;
    value  = tile_value & BYTE_MASK;
    func_801A4BC0(x_left, y_top, value);
    x_right = x + 0xC;
    func_801A4BC0(x_right, y_top, value);
    y_bottom = y + 0xB2;
    func_801A4BC0(x_left, y_bottom, value);
    func_801A4BC0(x_right, y_bottom, value);
}

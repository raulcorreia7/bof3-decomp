#include "area135_14.h"

MATCH void func_801F46AC(void) {
    s16 height;
    s16 highest;
    s32 x;
    s32 hi;
    s32 y;
    u8  col;
    u8  row;
    u8  selection;

    highest = -0x8000;
    y       = SELF(Actor)->pos.y.fixed - 0x8000;
    row     = 0;
    do {
        x   = SELF(Actor)->pos.x.fixed + 0xFFFE8000;
        col = 0;
        do {
            g_AreaHeightOffsetEnabled = 1;
            height                    = Area_HeightRead(x, y);
            if (highest < height) {
                highest = height;
            }
            col++;
            hi = x >> 16;
            x &= 65535;
            x |= (hi + 1) << 16;
        } while (col < 4);
        row++;
        hi = y >> 16;
        y &= 65535;
        y |= (hi + 1) << 16;
    } while (row < 2);
    selection                   = func_801F5C60(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed);
    g_SceneEventState.selection = selection;
    if (selection != 0xFF) {
        func_801F5BCC(Area_HeightSample(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed) + 0x280);
    } else {
        func_801F5BCC(highest + 0x180);
    }
}

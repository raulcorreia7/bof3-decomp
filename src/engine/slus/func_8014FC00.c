#include "engine/slus/slus.h"

/* Matching constraints of the shape. */

/* builds the texture-page draw-mode word for the current graphics mode. */
MATCH void func_8014FC00(s32 mode) {
    s32 draw_mode;
    u32 tpage;

    if (GetGraphType() == 1 || GetGraphType() == 2) {
        draw_mode = (((u32)(mode & 0x300) >> 3) | 0x8F);
    } else {
        tpage     = (((u32)(mode & 0x100)) >> 4) | 0x2F;
        draw_mode = (tpage | (((mode & 0x200)) << 2));
    }
    GFX_AddDrawMode(draw_mode);
}

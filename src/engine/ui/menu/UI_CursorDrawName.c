#include "engine/game/00/game_00.h"

/* draws the underline of the current name-entry letter: bright when the mode is 0, dim otherwise */
/* func_801AE214 */
MATCH void UI_CursorDrawName(s32 line_x, s32 line_y, s32 line_length, s32 line_mode) {
    s32      x;
    s32      y;
    u8       mode;
    s32      delta;
    u8       color;
    LINE_F2* line;

    line = (LINE_F2*)g_GfxPrimCursor;
    x    = line_x;
    y    = line_y;
    /* FAKE: the block holds this run in place; without it the match is 97.44%. */
    do {
        delta = line_length;
        SetLineF2(line);
        mode  = line_mode;
        color = 40;
        if (mode == 0) {
            color = 140;
        }
        line->r0 = color;
        line->g0 = color;
    } while (0);
    line->b0 = color;
    line->x0 = x;
    line->x1 = (x + delta);
    line->y1 = y;
    line->y0 = y;
    GFX_AddPrim(GFX_LAYER_UI, sizeof(LINE_F2));
}

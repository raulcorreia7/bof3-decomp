#include "game_00.h"

MATCH void UI_DrawSprite(s16 x, s16 y, u8 sprite_id, u8 flags) {
    u8*   rect;
    SPRT* sprt;

    rect = func_801AF270(sprite_id, flags & 1);
    sprt = (SPRT*)g_GfxPrimCursor;

    SetSprt(sprt);
    SetSemiTrans(sprt, 0);

    sprt->x0 = x;
    sprt->y0 = y;

    sprt->u0 = rect[0];
    sprt->v0 = rect[1];
    sprt->w  = rect[2];
    sprt->h  = rect[3];

    if (!(flags & 2)) {
        sprt->clut = GetClut(176, 481);
    } else {
        sprt->clut = GetClut(128, 482);
    }

    sprt->r0 = 128;
    sprt->g0 = 128;
    sprt->b0 = 128;
    GFX_AddPrim(1, 20);
}

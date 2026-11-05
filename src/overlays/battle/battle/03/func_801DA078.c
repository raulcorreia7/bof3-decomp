/* NOTE: measurement guard only. Landing needs
 * `void func_801DA078(s32 x, s32 y, s32 u_index);` in battle_03.h:312
 * and this guard removed. */
#define func_801DA078 func_801DA078_decl_guard
#include "battle_03.h"
#undef func_801DA078

MATCH void func_801DA078(s32 x, s32 y, s32 u_index) {
    SPRT* sprite;
    s32   texture_u;

    GFX_AddDrawMode(GetTPage(0, 1, FONT_TPAGE_X, FONT_TPAGE_Y));

    texture_u    = (u_index & BYTE_MASK) << 4;
    sprite       = (SPRT*)g_GfxPrimCursor;
    sprite->w    = 16;
    sprite->h    = 8;
    sprite->clut = 0x7800;
    PSX_SET_NEUTRAL_RGB(sprite);
    sprite->v0 = 216;
    sprite->u0 = texture_u;
    sprite->x0 = x;
    sprite->y0 = y;
    SetSprt(sprite);
    GFX_AddPrim(1, 0x14);
}

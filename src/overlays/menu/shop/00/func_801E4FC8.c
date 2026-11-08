#include "shop_00.h"

/* Shop sprite atlas records: u, v, clut x, clut y (4-byte stride). */

MATCH void func_801E4FC8(s32 sprite_x, s32 sprite_y, u8 atlas_index, s32 shade_mode) {
    SPRT*               sprt;
    MenuPortraitSprite* entry;
    s32                 shade;
    s32                 tpage;
    u16                 clut;

    if (atlas_index == 4 && g_SceneState.scenario_id >= 8) {
        atlas_index = 0xB;
    }
    entry = &g_ShopPortraitAtlas[atlas_index & BYTE_MASK];

    tpage = getTPage(0, 0, 896, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(1, sizeof(DR_MODE));

    sprt = (SPRT*)g_GfxPrimCursor;
    SetSprt(sprt);

    shade = shade_mode & BYTE_MASK;
    if (shade == 0) {
        sprt->b0 = 0x80;
        sprt->g0 = 0x80;
        sprt->r0 = 0x80;
    } else if (shade == 1) {
        sprt->b0 = 0x30;
        sprt->g0 = 0x30;
        sprt->r0 = 0x30;
    } else {
        sprt->g0 = 0x40;
        sprt->r0 = 0x40;
        sprt->b0 = 0x80;
    }

    setXY0(sprt, sprite_x, sprite_y);
    setUV0(sprt, entry->u + 3, entry->v + 5);
    clut = getClut(entry->clut_x, entry->clut_y + 0x1E0);
    setWH(sprt, 36, 40);
    sprt->clut = clut;
    GFX_AddPrim(1, sizeof(SPRT));
}

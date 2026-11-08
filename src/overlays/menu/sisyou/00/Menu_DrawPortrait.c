#include "sisyou_00.h"

/* g_EmiLoadedCharacterIndex, the front-end mode byte owned by the main executable:
 * the low 7 bits select the current mode. */

/* Panel atlas records: u, v, clut x, clut y (4-byte stride). */

MATCH void Menu_DrawPortrait(u16 x, u16 y, u8 sprite_id, u8 shade) {
    SPRT*               sprt;
    MenuPortraitSprite* entry;
    s32                 shade_value;
    s32                 tpage;
    u16                 clut;

    if ((sprite_id & BYTE_MASK) == 4 && (g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK) != 5 &&
        (g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK) != 0xC) {
        sprite_id = 0xB;
    }
    entry = &g_MenuPortraitAtlas[sprite_id & BYTE_MASK];

    tpage = getTPage(0, 0, 896, 256);
    GFX_AddDitheredDrawMode(1, tpage);

    sprt = (SPRT*)g_GfxPrimCursor;
    SetSprt(sprt);

    shade_value = shade & BYTE_MASK;
    /* Retail writes b0, g0, r0 as one block in the first two arms. */
    if (shade_value == 0) {
        sprt->b0 = GFX_COLOR_NEUTRAL;
        sprt->g0 = GFX_COLOR_NEUTRAL;
        sprt->r0 = GFX_COLOR_NEUTRAL;
    } else if (shade_value == 1) {
        sprt->b0 = 48;
        sprt->g0 = 48;
        sprt->r0 = 48;
    } else {
        sprt->g0 = 64;
        sprt->r0 = 64;
        sprt->b0 = GFX_COLOR_NEUTRAL;
    }

    setXY0(sprt, x, y);
    setUV0(sprt, entry->u, entry->v);
    clut = getClut(entry->clut_x, entry->clut_y + 0x1E0);
    setWH(sprt, 40, 48);
    sprt->clut = clut;
    GFX_AddPrim(1, sizeof(SPRT));
}

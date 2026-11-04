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
    entry = &D_801D4058[sprite_id & BYTE_MASK];

    tpage = getTPage(0, 0, 896, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(1, 0xC);

    sprt = (SPRT*)g_GfxPrimCursor;
    SetSprt(sprt);

    shade_value = shade & BYTE_MASK;
    /* Retail writes b0, g0, r0 as one block in the first two arms. */
    if (shade_value == 0) {
        sprt->b0 = 0x80;
        sprt->g0 = 0x80;
        sprt->r0 = 0x80;
    } else if (shade_value == 1) {
        sprt->b0 = 0x30;
        sprt->g0 = 0x30;
        sprt->r0 = 0x30;
    } else {
        sprt->g0 = 0x40;
        sprt->r0 = 0x40;
        sprt->b0 = 0x80;
    }

    sprt->x0   = x;
    sprt->y0   = y;
    sprt->u0   = entry->u;
    sprt->v0   = entry->v;
    clut       = getClut(entry->clut_x, entry->clut_y + 0x1E0);
    sprt->w    = 40;
    sprt->h    = 48;
    sprt->clut = clut;
    GFX_AddPrim(1, 0x14);
}

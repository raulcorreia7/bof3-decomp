#include "area030_04.h"

#ifdef NON_MATCHING
/* Draws one character in the fishing interface. */
NON_MATCHING void func_801D9740(s32 color, u8* pixels, s32 mask, s32 value) {
    POLY_FT4* quad;

    quad = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(quad);
    switch (*pixels) {
        case 0x15:
            pixels++;
            quad->tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 960, 0);
            setUV0(quad, ((*pixels + 91) % 21) * 12, ((*pixels + 91) / 21) * 12);
            break;
        case 0x12:
        case 0x13:
            quad->tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 960, 256);
            if (*pixels == 0x12) {
                pixels++;
                setUV0(quad, (u8)(*pixels % 21) * 12, (u8)(*pixels / 21) * 12);
            } else {
                pixels++;
                setUV0(quad, ((*pixels + 256) % 21) * 12, ((*pixels + 256) / 21) * 12);
            }
            break;
        default:
            quad->tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 960, 0);
            setUV0(quad, ((*pixels - 48) % 31) * 8, ((*pixels - 48) / 31) * 12 + 72);
            break;
    }
    if (mask & 0x80) {
        quad->u0 += 8 - (mask & 0x7F);
    }
    quad->x1 = value + (mask & 0x7F);
    quad->x0 = value;
    setUVWH(quad, quad->u0, quad->v0, mask & 0x7F, 12);
    quad->x2 = quad->x0;
    quad->x3 = quad->x1;
    setRGB0(quad, 128, 128, 128);
    quad->y0   = g_SpawnedActors[3].screen_y + 3;
    quad->clut = getClut((color & 0xF) * 16, 480);
    quad->y1   = quad->y0;
    quad->y2   = quad->y0 + 12;
    quad->y3   = quad->y2;
    GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_FT4));
}
#else
INCLUDE_ASM(func_801D9740);
#endif

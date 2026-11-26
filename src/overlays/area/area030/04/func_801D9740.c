#include "area030_04.h"

/* Draws one character in the fishing interface. */
// clang-format off
MATCH void func_801D9740(color, pixels, mask, value)
u8 color;
u8* pixels;
u8 mask;
s16 value;
// clang-format on
{
    POLY_FT4* quad;
    s16       top;

    quad = GFX_CURSOR(POLY_FT4);
    SetPolyFT4(quad);
    switch (*pixels) {
        case 0x15:
            pixels++;
            quad->tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 960, 0);
            setUV0(quad, ((*pixels + 91) % 21) * 12, ((*pixels + 91) / 21) * 12);
            break;
        case 0x12:
        case 0x13:
            quad->tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 960, 256);
            if (*pixels == 0x12) {
                pixels++;
                setUV0(quad, (u8)(*pixels % 21) * 12, (u8)(*pixels / 21) * 12);
            } else {
                pixels++;
                setUV0(quad, ((*pixels + 256) % 21) * 12, ((*pixels + 256) / 21) * 12);
            }
            break;
        default:
            quad->tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 960, 0);
            setUV0(quad, ((*pixels - 48) % 31) * 8, ((*pixels - 48) / 31) * 12 + 72);
            break;
    }
    if (mask & 0x80) {
        quad->u0 += 8;
        quad->u0 -= (mask & 0x7F);
    }
    quad->x0 = value;
    quad->x1 = value + (mask & 0x7F);
    /* setUVWH would also store u0 and v0, which the original does not. */
    quad->u1 = quad->u0 + (mask & 0x7F);
    quad->u2 = quad->u0;
    quad->u3 = quad->u1;
    quad->v1 = quad->v0;
    quad->v2 = quad->v0 + 12;
    quad->v3 = quad->v2;
    quad->x2 = quad->x0;
    quad->x3 = quad->x1;
    top      = g_SpawnedActors[3].screen_y + 3;
    PSX_SET_NEUTRAL_RGB(quad);
    quad->y0   = top;
    quad->clut = getClut((color & 0xF) * 16, 480);
    quad->y1   = top;
    quad->y2   = quad->y0 + 12;
    quad->y3   = quad->y2;
    GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_FT4));
}

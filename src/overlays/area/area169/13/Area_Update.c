#include "area169_13.h"

/* Draws the area169 floor quad twice, once per sprite row: the corners start level
 * with the work record's ground, then each pass spreads them by the row's scale and
 * queues its cell primitive. */
MATCH void Area_Update(void) {
    POLY_FT4*    prim;
    long         depth;
    long         flag;
    s32          i;
    s16          product;
    s16          offset;
    s16          corner;
    s8           bias;
    volatile u8* scale;

    if (SELF(Actor)->direction != 0) {
        g_ScratchPadVectors[0].vy = g_ScratchPadVectors[1].vy = g_ScratchPadVectors[2].vy = g_ScratchPadVectors[3].vy = ((FIX_INT(SELF(Actor)->pos.y.fixed) - 0x80) << 7) | 0x40;
    } else {
        g_ScratchPadVectors[0].vx = g_ScratchPadVectors[1].vx = g_ScratchPadVectors[2].vx = g_ScratchPadVectors[3].vx = ((FIX_INT(SELF(Actor)->pos.x.fixed) - 0x80) << 7) | 0x40;
    }

    g_ScratchPadVectors[0].vz = g_ScratchPadVectors[1].vz = (u16)SELF(Actor)->pos.z.part.integer - 0x180;
    g_ScratchPadVectors[2].vz = g_ScratchPadVectors[3].vz = (u16)SELF(Actor)->pos.z.part.integer;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256), NULL);
    GFX_AddPrim(GFX_LAYER_FIELD_SCENE, sizeof(DR_MODE));
    scale = D_801F3AAC;
    for (i = 0; i < 2; i++) {
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        if (SELF(Actor)->direction != 0) {
            bias                      = (s8)scale[i];
            product                   = SELF(Actor)->screen_y * bias;
            offset                    = product + 0x40;
            corner = ((FIX_INT(SELF(Actor)->pos.x.fixed) - 0x7F) << 7);
            corner += offset;
            g_ScratchPadVectors[0].vx = g_ScratchPadVectors[2].vx = corner;
            bias                                                  = (s8)scale[i];
            product                                               = SELF(Actor)->screen_y * bias;
            offset                                                = product - 0x40;
            corner = ((FIX_INT(SELF(Actor)->pos.x.fixed) - 0x80) << 7);
            corner += offset;
            g_ScratchPadVectors[1].vx = g_ScratchPadVectors[3].vx = corner;
        } else {
            bias                      = (s8)scale[i];
            product                   = SELF(Actor)->screen_y * bias;
            offset                    = product + 0x40;
            corner = ((FIX_INT(SELF(Actor)->pos.y.fixed) - 0x7F) << 7);
            corner += offset;
            g_ScratchPadVectors[0].vy = g_ScratchPadVectors[2].vy = corner;
            bias                                                  = (s8)scale[i];
            product                                               = SELF(Actor)->screen_y * bias;
            offset                                                = product - 0x40;
            corner = ((FIX_INT(SELF(Actor)->pos.y.fixed) - 0x80) << 7);
            corner += offset;
            g_ScratchPadVectors[1].vy = g_ScratchPadVectors[3].vy = corner;
        }
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        Area_ApplyTileToQuad((SELF(Actor)->direction << 21) | (0x1251 << 16) | (0x10C - i), prim, 1);
        GFX_AddPrim(GFX_LAYER_FIELD_SCENE, sizeof(POLY_FT4));
    }
}

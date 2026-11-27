#include "area174_13.h"

/* Draws the area174 floor quad twice, once per sprite row: each pass spreads the
 * corners by the row's screen scale, squashes them to the ground, and queues the
 * draw mode, its cell primitive and the quad. */
MATCH void Area_Update(void) {
    POLY_FT4*    prim;
    long         depth;
    long         flag;
    s32          i;
    s32          edge_x;
    s32          edge_y;
    s32          product;
    s32          offset;
    s8           bias;
    volatile u8* scale;

    if (SELF(Actor)->direction != 0) {
        g_ScratchPadVectors[0].vy = g_ScratchPadVectors[1].vy = g_ScratchPadVectors[2].vy = g_ScratchPadVectors[3].vy = ((FIX_INT(SELF(Actor)->pos.y.fixed) - 0x80) << 7) | 0x40;
    } else {
        g_ScratchPadVectors[0].vx = g_ScratchPadVectors[1].vx = g_ScratchPadVectors[2].vx = g_ScratchPadVectors[3].vx = ((FIX_INT(SELF(Actor)->pos.x.fixed) - 0x80) << 7) | 0x40;
    }

    g_ScratchPadVectors[0].vz = g_ScratchPadVectors[1].vz = (u16)SELF(Actor)->pos.z.part.integer - SELF(Actor)->screen_x;
    g_ScratchPadVectors[2].vz = g_ScratchPadVectors[3].vz = (u16)SELF(Actor)->pos.z.part.integer;

    scale = D_801F4FE4;
    for (i = 0; i < 2; i++) {
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256), NULL);
        Area_CellAddPrim(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, -1, sizeof(DR_MODE));
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        if (SELF(Actor)->direction != 0) {
            bias                      = (s8)scale[i];
            product                   = SELF(Actor)->screen_y * bias;
            offset                    = product + 0x40;
            edge_x                    = i - 0x80;
            g_ScratchPadVectors[0].vx = g_ScratchPadVectors[2].vx = ((FIX_INT(SELF(Actor)->pos.x.fixed) + edge_x) << 7) - offset;
            bias                                                  = (s8)scale[i];
            product                                               = SELF(Actor)->screen_y * bias;
            offset                                                = product - 0x40;
            g_ScratchPadVectors[1].vx = g_ScratchPadVectors[3].vx = ((FIX_INT(SELF(Actor)->pos.x.fixed) + edge_x) << 7) - offset;
        } else {
            bias                      = (s8)scale[i];
            product                   = SELF(Actor)->screen_y * bias;
            offset                    = product + 0x40;
            edge_y                    = i + 0x7F;
            g_ScratchPadVectors[0].vy = g_ScratchPadVectors[2].vy = ((FIX_INT(SELF(Actor)->pos.y.fixed) - edge_y) << 7) + offset;
            bias                                                  = (s8)scale[i];
            product                                               = SELF(Actor)->screen_y * bias;
            offset                                                = product - 0x40;
            g_ScratchPadVectors[1].vy = g_ScratchPadVectors[3].vy = ((FIX_INT(SELF(Actor)->pos.y.fixed) - edge_y) << 7) + offset;
        }
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        Area_ApplyTileToQuad((SELF(Actor)->direction << 21) | (SELF(Actor)->gravity + i), prim, 1);
        Area_CellAddPrim(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, -1, sizeof(POLY_FT4));
    }
}

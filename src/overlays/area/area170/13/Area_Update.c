#include "area170_13.h"

/* Draws the area170 floor quad twice, once per sprite row: the four corner vectors the GTE
 * projects, the row's screen scale, and the cell primitive before and after each quad. */
/* Area_HeightSample, Area_ApplyTileToQuad and the scale row are not declared by the shared headers. */
s16 Area_HeightSample(s32 x, s32 y);
s32 Area_ApplyTileToQuad(u32 part_word, POLY_FT4* prim, s32 mode);

MATCH void Area_Update(void) {
    POLY_FT4* prim;
    long      depth;
    long      flag;
    s32       i;
    s32       y;
    s32       x;
    s32       y1;
    s32       x1;
    s8        bias;
    s32       product;
    s32       offset;
    u8*       scale;

    if (SELF(Actor)->direction != 0) {
        g_ScratchPadVectors[0].vy = g_ScratchPadVectors[1].vy = g_ScratchPadVectors[2].vy = g_ScratchPadVectors[3].vy = ((FIX_INT(SELF(Actor)->pos.y.fixed) - 0x80) << 7) | 0x40;
    } else {
        g_ScratchPadVectors[0].vx = g_ScratchPadVectors[1].vx = g_ScratchPadVectors[2].vx = g_ScratchPadVectors[3].vx = ((FIX_INT(SELF(Actor)->pos.x.fixed) - 0x80) << 7) | 0x40;
    }

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256), NULL);
    GFX_AddPrim(GFX_LAYER_FIELD_SCENE, sizeof(DR_MODE));
    scale = D_801F58B8;
    for (i = 0; i < 2; i++) {
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        if (SELF(Actor)->direction != 0) {
            bias                      = FAKE_VOLATILE(u8, scale[i]); /* FAKE: retail loads the scale unsigned and sign-extends it apart; the volatile read keeps the two steps. */
            product                   = SELF(Actor)->screen_y * bias;
            offset                    = product + 0x40;
            g_ScratchPadVectors[0].vx = g_ScratchPadVectors[2].vx = ((FIX_INT(SELF(Actor)->pos.x.fixed) - 0x7F) << 7) + offset;
            bias                      = FAKE_VOLATILE(u8, scale[i]); /* FAKE: retail loads the scale unsigned and sign-extends it apart; the volatile read keeps the two steps. */
            product                   = SELF(Actor)->screen_y * bias;
            offset                    = product - 0x40;
            g_ScratchPadVectors[1].vx = g_ScratchPadVectors[3].vx = ((FIX_INT(SELF(Actor)->pos.x.fixed) - 0x80) << 7) + offset;
        } else {
            bias                      = FAKE_VOLATILE(u8, scale[i]); /* FAKE: retail loads the scale unsigned and sign-extends it apart; the volatile read keeps the two steps. */
            product                   = SELF(Actor)->screen_y * bias;
            offset                    = product + 0x40;
            g_ScratchPadVectors[0].vy = g_ScratchPadVectors[2].vy = ((FIX_INT(SELF(Actor)->pos.y.fixed) - 0x7F) << 7) + offset;
            bias                      = FAKE_VOLATILE(u8, scale[i]); /* FAKE: retail loads the scale unsigned and sign-extends it apart; the volatile read keeps the two steps. */
            product                   = SELF(Actor)->screen_y * bias;
            offset                    = product - 0x40;
            g_ScratchPadVectors[1].vy = g_ScratchPadVectors[3].vy = ((FIX_INT(SELF(Actor)->pos.y.fixed) - 0x80) << 7) + offset;
        }
        x                         = (g_ScratchPadVectors[0].vx + 0x4000) << 9;
        y                         = (g_ScratchPadVectors[0].vy + 0x4000) << 9;
        g_ScratchPadVectors[0].vz = -Area_HeightSample(x, y) / 2 - (u16)SELF(Actor)->pos.z.part.integer - 0x180;
        g_ScratchPadVectors[2].vz = -Area_HeightSample(x, y) / 2 - (u16)SELF(Actor)->pos.z.part.integer;
        x1                        = (g_ScratchPadVectors[1].vx + 0x4000) << 9;
        y1                        = (g_ScratchPadVectors[1].vy + 0x4000) << 9;
        g_ScratchPadVectors[1].vz = -Area_HeightSample(x1, y1) / 2 - (u16)SELF(Actor)->pos.z.part.integer - 0x180;
        g_ScratchPadVectors[3].vz = -Area_HeightSample(x1, y1) / 2 - (u16)SELF(Actor)->pos.z.part.integer;
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        Area_ApplyTileToQuad((SELF(Actor)->direction << 21) | (0x2551 << 16) | (0x127 - i), prim, 1);
        GFX_AddPrim(GFX_LAYER_FIELD_SCENE, sizeof(POLY_FT4));
    }
}

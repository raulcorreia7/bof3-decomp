#include "area171_13.h"

/* Draws the entry cell's two quads along the floor. */
MATCH void func_801F3070(s32 sample_ground) {
    POLY_FT4* prim;
    long      depth;
    long      flag;
    void*     xy0;
    void*     xy1;
    void*     xy2;
    void*     xy3;
    s32       i;
    s32       x;
    s32       y;
    s32       far_y;
    s32       far_row;
    s32       tpage;
    s32       row_offset;

    x                         = ((SELF(Actor)->pos.x.part.integer - 0x80) << 7) + 0x40;
    g_ScratchPadVectors[0].vx = g_ScratchPadVectors[1].vx = g_ScratchPadVectors[2].vx = g_ScratchPadVectors[3].vx = x;

    tpage = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_LAYER_DRAW_MODE(GFX_LAYER_FIELD_SCENE, tpage);

    for (i = 0; i < 2; i++) {
        prim = GFX_CURSOR(POLY_FT4);
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        /* FAKE: keeps the step load unsigned until the multiply (26 rows with plain C). */
        row_offset                = (u16)SELF(Actor)->screen_y * (s8)FAKE_VOLATILE(u8, D_801F3F84[i]) + 0x40;
        y                         = ((SELF(Actor)->pos.y.part.integer - 0x7F) << 7) + row_offset;
        g_ScratchPadVectors[0].vy = g_ScratchPadVectors[2].vy = y;

        /* FAKE: keeps the second step load unsigned until the multiply (26 rows with plain C). */
        row_offset                = (u16)SELF(Actor)->screen_y * (s8)FAKE_VOLATILE(u8, D_801F3F84[i]) - 0x40;
        far_y                     = ((SELF(Actor)->pos.y.part.integer - 0x80) << 7) + row_offset;
        g_ScratchPadVectors[1].vy = g_ScratchPadVectors[3].vy = far_y;

        if (sample_ground != 0) {
            x = g_ScratchPadVectors[0].vx;
            x += 0x4000;
            x <<= 9;
            y <<= 16;
            y >>= 16;
            y += 0x4000;
            y <<= 9;
            g_ScratchPadVectors[0].vz = -Area_HeightSample(x, y) / 2 - SELF(Actor)->pos.z.part.integer - 0x180;
            g_ScratchPadVectors[2].vz = -Area_HeightSample(x, y) / 2 - SELF(Actor)->pos.z.part.integer;
            y                         = g_ScratchPadVectors[1].vx;
            y += 0x4000;
            y <<= 9;
            far_row                   = g_ScratchPadVectors[1].vy;
            g_ScratchPadVectors[1].vz = -Area_HeightSample(y, (far_row + 0x4000) << 9) / 2 - SELF(Actor)->pos.z.part.integer - 0x180;
            g_ScratchPadVectors[3].vz = -Area_HeightSample(y, (far_row + 0x4000) << 9) / 2 - SELF(Actor)->pos.z.part.integer;
        } else {
            g_ScratchPadVectors[0].vz = g_ScratchPadVectors[1].vz = SELF(Actor)->unk_32 - 0x180;
            g_ScratchPadVectors[2].vz = g_ScratchPadVectors[3].vz = SELF(Actor)->unk_32;
        }
        xy0 = &prim->x0;
        xy1 = &prim->x1;
        xy2 = &prim->x2;
        xy3 = &prim->x3;
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], xy0, xy1, xy2, xy3, &depth, &flag);
        Area_ApplyTileToQuad((SELF(Actor)->vx | (0x169 << 16)) | (0x130 - i), prim, 1);
        GFX_AddPrim(GFX_LAYER_FIELD_SCENE, sizeof(POLY_FT4));
    }
}

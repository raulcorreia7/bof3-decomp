#include "area167_13.h"

/* Draws the area167 floor quad twice, once per sprite row: the four corner vectors the GTE
 * projects, the row's screen scale, and the cell primitive before and after each quad. */
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
    s16       product;
    s16       offset;
    s16       corner;
    u8*       scale;
    s32       edge_x;
    s32       edge_y;

    if (SELF(Actor)->direction != 0) {
        g_ScratchPadVectors[0].vy = g_ScratchPadVectors[1].vy = g_ScratchPadVectors[2].vy = g_ScratchPadVectors[3].vy = ((FIX_INT(SELF(Actor)->pos.y.fixed) - 0x80) << 7) | 0x40;
    } else {
        g_ScratchPadVectors[0].vx = g_ScratchPadVectors[1].vx = g_ScratchPadVectors[2].vx = g_ScratchPadVectors[3].vx = ((FIX_INT(SELF(Actor)->pos.x.fixed) - 0x80) << 7) | 0x40;
    }

    scale = D_801F4A68 + AREA_ROW_SCALE_OFFSET;
    for (i = 0; i < 2; i++) {
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256), NULL);
        Area_CellAddPrim(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, -1, sizeof(DR_MODE));
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        if (SELF(Actor)->direction != 0) {
            edge_x                    = i - 0x80;
            bias                      = scale[i];
            product                   = SELF(Actor)->screen_y * bias;
            offset                    = product + 0x40;
            g_ScratchPadVectors[0].vx = g_ScratchPadVectors[2].vx = ((FIX_INT(SELF(Actor)->pos.x.fixed) + edge_x) << 7) - offset;
            bias                                                  = scale[i];
            product                                               = SELF(Actor)->screen_y * bias;
            offset                                                = product - 0x40;
            g_ScratchPadVectors[1].vx = g_ScratchPadVectors[3].vx = ((FIX_INT(SELF(Actor)->pos.x.fixed) + edge_x) << 7) - offset;
        } else {
            edge_y  = i + 0x7F;
            bias    = scale[i];
            product = SELF(Actor)->screen_y * bias;
            offset  = product + 0x40;
            corner  = ((FIX_INT(SELF(Actor)->pos.y.fixed) - edge_y) << 7);
            corner += offset;
            g_ScratchPadVectors[0].vy = g_ScratchPadVectors[2].vy = corner;
            bias                                                  = scale[i];
            product                                               = SELF(Actor)->screen_y * bias;
            offset                                                = product - 0x40;
            corner                                                = ((FIX_INT(SELF(Actor)->pos.y.fixed) - edge_y) << 7);
            corner += offset;
            g_ScratchPadVectors[1].vy = g_ScratchPadVectors[3].vy = corner;
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
        Area_ApplyTileToQuad((SELF(Actor)->direction << 21) | (SELF(Actor)->gravity + i), prim, 1);
        Area_CellAddPrim(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, -1, sizeof(POLY_FT4));
    }
}

#include "area157_13.h"

/* Draws the area157 floor quad at the work record's cell: the four corner vectors the GTE
 * projects, the tile word of the sprite row, and the cell primitive before and after it. */
MATCH void Area_Update(void) {
    POLY_FT4* prim;
    long      depth;
    long      flag;
    s8        bias;
    s16       product;
    s16       offset;
    s16       corner;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256), NULL);
    Area_CellAddPrim(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, -2, sizeof(DR_MODE));
    prim = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    SetShadeTex(prim, 0);
    if (SELF(Actor)->direction != 0) {
        g_ScratchPadVectors[0].vy = g_ScratchPadVectors[1].vy = g_ScratchPadVectors[2].vy = g_ScratchPadVectors[3].vy = ((FIX_INT(SELF(Actor)->pos.y.fixed) - 0x80) << 7) | 0x40;
        bias = D_801F38CC[AREA_ROW_SCALE_OFFSET + SELF(Actor)->unk_0A];
        product                   = SELF(Actor)->screen_y * bias;
        offset                    = product - 0x40;
        g_ScratchPadVectors[0].vx = g_ScratchPadVectors[2].vx = ((FIX_INT(SELF(Actor)->pos.x.fixed) - 0x7F) << 7) - offset;
        bias = D_801F38CC[AREA_ROW_SCALE_OFFSET + SELF(Actor)->unk_0A];
        product                   = SELF(Actor)->screen_y * bias;
        offset                    = product + 0x40;
        g_ScratchPadVectors[1].vx = g_ScratchPadVectors[3].vx = ((FIX_INT(SELF(Actor)->pos.x.fixed) - 0x80) << 7) - offset;
    } else {
        g_ScratchPadVectors[0].vx = g_ScratchPadVectors[1].vx = g_ScratchPadVectors[2].vx = g_ScratchPadVectors[3].vx = ((FIX_INT(SELF(Actor)->pos.x.fixed) - 0x80) << 7) | 0x40;
        bias = D_801F38CC[AREA_ROW_SCALE_OFFSET + SELF(Actor)->unk_0A];
        product                   = SELF(Actor)->screen_y * bias;
        offset                    = product + 0x40;
        corner = ((FIX_INT(SELF(Actor)->pos.y.fixed) - 0x7F) << 7);
        corner += offset;
        g_ScratchPadVectors[0].vy = g_ScratchPadVectors[2].vy = corner;
        bias = D_801F38CC[AREA_ROW_SCALE_OFFSET + SELF(Actor)->unk_0A];
        product                   = SELF(Actor)->screen_y * bias;
        offset                    = product - 0x40;
        corner = ((FIX_INT(SELF(Actor)->pos.y.fixed) - 0x80) << 7);
        corner += offset;
        g_ScratchPadVectors[1].vy = g_ScratchPadVectors[3].vy = corner;
    }
    g_ScratchPadVectors[0].vz = g_ScratchPadVectors[1].vz = (u16)SELF(Actor)->pos.z.part.integer - 0x140;
    g_ScratchPadVectors[2].vz = g_ScratchPadVectors[3].vz = (u16)SELF(Actor)->pos.z.part.integer;
    RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth,
                  &flag);
    Area_ApplyTileToQuad((0x150 << 16) | 0x117 | (SELF(Actor)->direction << 21) | ((SELF(Actor)->unk_0A ^ (SELF(Actor)->direction == 0)) << 16), prim, 1);
    Area_CellAddPrim(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, -2, sizeof(POLY_FT4));
}

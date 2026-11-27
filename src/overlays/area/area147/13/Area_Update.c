#include "area147_13.h"

/* Draws the area147 floor quad once per part row, then the extra quad the work
 * record's unk_32 row selects, and queues each cell primitive. */
MATCH void Area_Update(s32 arg) {
    POLY_FT4* prim;
    long      depth;
    long      flag;
    s32       i;
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

    g_ScratchPadVectors[0].vz = g_ScratchPadVectors[1].vz = (u16)SELF(Actor)->pos.z.part.integer - 0x180;
    g_ScratchPadVectors[2].vz = g_ScratchPadVectors[3].vz = (u16)SELF(Actor)->pos.z.part.integer;

    scale = (u8*)D_801F35D8;
    for (i = 0; i < 2; i++) {
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        if (SELF(Actor)->direction != 0) {
            edge_x                    = i - 0x80;
            bias                      = scale[i];
            product                   = SELF(Actor)->screen_y * bias;
            offset                    = product + 0x40;
            g_ScratchPadVectors[0].vx = g_ScratchPadVectors[2].vx = ((FIX_INT(SELF(Actor)->pos.x.fixed) + edge_x) << 7) - offset;
            bias                      = scale[i];
            product                   = SELF(Actor)->screen_y * bias;
            offset                    = product - 0x40;
            g_ScratchPadVectors[1].vx = g_ScratchPadVectors[3].vx = ((FIX_INT(SELF(Actor)->pos.x.fixed) + edge_x) << 7) - offset;
        } else {
            edge_y                    = i + 0x7F;
            bias                      = scale[i];
            product                   = SELF(Actor)->screen_y * bias;
            offset                    = product + 0x40;
            corner = ((FIX_INT(SELF(Actor)->pos.y.fixed) - edge_y) << 7);
            corner += offset;
            g_ScratchPadVectors[0].vy = g_ScratchPadVectors[2].vy = corner;
            bias                      = scale[i];
            product                   = SELF(Actor)->screen_y * bias;
            offset                    = product - 0x40;
            corner = ((FIX_INT(SELF(Actor)->pos.y.fixed) - edge_y) << 7);
            corner += offset;
            g_ScratchPadVectors[1].vy = g_ScratchPadVectors[3].vy = corner;
        }
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        Area_ApplyTileToQuad((SELF(Actor)->direction << 21) | AREA147_FLOOR_PART_WORD | ((s16)SELF(Actor)->screen_x + i), prim, 1);
        Area_CellAddPrim(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, (s8)arg, sizeof(POLY_FT4));
    }

    if (SELF(Actor)->unk_32 != 0) {
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        if (SELF(Actor)->direction != 0) {
            g_ScratchPadVectors[0].vx = g_ScratchPadVectors[2].vx = (FIX_INT(SELF(Actor)->pos.x.fixed) << 7) - 0x40C0;
            g_ScratchPadVectors[1].vx = g_ScratchPadVectors[3].vx = ((FIX_INT(SELF(Actor)->pos.x.fixed) - 0x81) << 7) | 0x40;
        } else {
            g_ScratchPadVectors[0].vy = g_ScratchPadVectors[2].vy = ((FIX_INT(SELF(Actor)->pos.y.fixed) - 0x81) << 7) | 0x40;
            g_ScratchPadVectors[1].vy = g_ScratchPadVectors[3].vy = (FIX_INT(SELF(Actor)->pos.y.fixed) << 7) - 0x40C0;
        }
        g_ScratchPadVectors[0].vz = g_ScratchPadVectors[1].vz = (u16)SELF(Actor)->pos.z.part.integer - 0x140;
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        Area_ApplyTileToQuad(D_801F35D8[SELF(Actor)->unk_32], prim, 1);
        Area_CellAddPrim(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, 0, sizeof(POLY_FT4));
    }
}

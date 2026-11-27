#include "area118_13.h"

/* The tile row the actor's facing picks and the page word Area_ApplyTileToQuad
 * stamps into the quad; the page's low half is the actor's screen x. */
#define AREA118_FLOOR_QUAD_DIRECTION_STEP 0x29
#define AREA118_FLOOR_QUAD_SPRITE_WORD    (0x2650 << 16)

/* Lay the actor's floor quad on the cell: its long side follows the facing, and
 * the flag picks sampled terrain heights over the actor's cached height. */
MATCH void func_801F381C(s32 sample_height) {
    POLY_FT4* prim;
    long      depth;
    long      flag;
    s32       x;
    s32       y;
    s32       x1;
    s32       y1;

    if ((g_AreaDrawFlags & AREA_DRAW_CELL_LAYERS) == 0) {
        return;
    }
    GFX_ADD_LAYER_DRAW_MODE(GFX_LAYER_FIELD_SCENE, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256));
    prim = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    SetShadeTex(prim, 0);
    if (SELF(Actor)->direction != 0) {
        g_ScratchPadVectors[0].vy = g_ScratchPadVectors[1].vy = g_ScratchPadVectors[2].vy = g_ScratchPadVectors[3].vy = ((FIX_INT(SELF(Actor)->pos.y.fixed) - 0x80) << 7) | 0x40;
        g_ScratchPadVectors[0].vx = g_ScratchPadVectors[2].vx = ((FIX_INT(SELF(Actor)->pos.x.fixed) - 0x7F) << 7) - ((u16)SELF(Actor)->screen_y - 0x40);
        g_ScratchPadVectors[1].vx = g_ScratchPadVectors[3].vx = ((FIX_INT(SELF(Actor)->pos.x.fixed) - 0x80) << 7) - ((u16)SELF(Actor)->screen_y + 0x40);
    } else {
        g_ScratchPadVectors[0].vx = g_ScratchPadVectors[1].vx = g_ScratchPadVectors[2].vx = g_ScratchPadVectors[3].vx = ((FIX_INT(SELF(Actor)->pos.x.fixed) - 0x80) << 7) | 0x40;
        g_ScratchPadVectors[0].vy = g_ScratchPadVectors[2].vy = ((FIX_INT(SELF(Actor)->pos.y.fixed) - 0x7F) << 7) + ((u16)SELF(Actor)->screen_y + 0x40);
        g_ScratchPadVectors[1].vy = g_ScratchPadVectors[3].vy = ((FIX_INT(SELF(Actor)->pos.y.fixed) - 0x80) << 7) + (s16)(SELF(Actor)->screen_y - 0x40);
    }
    if (sample_height != 0) {
        x                         = (g_ScratchPadVectors[0].vx + 0x4000) << 9;
        y                         = (g_ScratchPadVectors[0].vy + 0x4000) << 9;
        g_ScratchPadVectors[0].vz = -Area_HeightSample(x, y) / 2 - (u16)COORD_INT(SELF(Actor)->pos.z) - 0x140;
        g_ScratchPadVectors[2].vz = -Area_HeightSample(x, y) / 2 - (u16)COORD_INT(SELF(Actor)->pos.z);
        x1                        = (g_ScratchPadVectors[1].vx + 0x4000) << 9;
        y1                        = (g_ScratchPadVectors[1].vy + 0x4000) << 9;
        g_ScratchPadVectors[1].vz = -Area_HeightSample(x1, y1) / 2 - (u16)COORD_INT(SELF(Actor)->pos.z) - 0x140;
        g_ScratchPadVectors[3].vz = -Area_HeightSample(x1, y1) / 2 - (u16)COORD_INT(SELF(Actor)->pos.z);
    } else {
        g_ScratchPadVectors[0].vz = g_ScratchPadVectors[1].vz = (u16)SELF(Actor)->unk_32 - 0x140;
        g_ScratchPadVectors[2].vz = g_ScratchPadVectors[3].vz = (u16)SELF(Actor)->unk_32;
    }
    RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth,
                  &flag);
    Area_ApplyTileToQuad((SELF(Actor)->direction * AREA118_FLOOR_QUAD_DIRECTION_STEP << 16) | AREA118_FLOOR_QUAD_SPRITE_WORD | (s16)SELF(Actor)->screen_x, prim, 1);
    GFX_AddPrim(GFX_LAYER_FIELD_SCENE, sizeof(POLY_FT4));
}

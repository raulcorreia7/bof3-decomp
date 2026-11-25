#include "area167_13.h"

#define AREA167_EFFECT_PART_WORD ((0xBB50u << 16) | 0x9100u)

#ifdef NON_MATCHING
/* Draws the falling effect as three widening quads, one per layer step. */
NON_MATCHING void func_801F39BC(void) {
    POLY_FT4* prim;
    SVECTOR*  quad;
    long      depth;
    long      flag;
    s32       x;
    s32       y;
    s32       layer;
    s32       size;
    s32       x_high;
    s32       y_high;
    s32       row;
    s32       side;
    s32       z;
    s32       left;
    s32       top;

    layer = TASK(Actor)->param.unk_0B - 0x4B;
    if (TASK(Actor)->header.step == 0) {
        TASK(Actor)->vy       = ((layer * 3) << 9) + 0xC00 + (rand() & 0xFF);
        side                  = COORD_FRAC(TASK(Actor)->pos.x) == 0;
        TASK(Actor)->screen_x = D_801F4AC4[side * 2];
        side                  = COORD_FRAC(TASK(Actor)->pos.x) == 0;
        TASK(Actor)->screen_y = D_801F4AC5[side * 2];
        COORD_INT(TASK(Actor)->pos.y) += rand() & 7;
        TASK(Actor)->header.step++;
    }
    if ((g_AreaDrawFlags & AREA_DRAW_CELL_LAYERS) == 0) {
        return;
    }

    TASK(Actor)->pos.y.fixed += TASK(Actor)->vy;
    if (COORD_INT(TASK(Actor)->pos.y) > (s16)TASK(Actor)->screen_y) {
        COORD_INT(TASK(Actor)->pos.y) = TASK(Actor)->screen_x;
    }

    x    = (TASK(Actor)->pos.x.fixed >> 9) - 0x4EC0;
    y    = (TASK(Actor)->pos.y.fixed >> 9) - (AREA_CELL_ORIGIN - AREA_CELL_HALF);
    size = ((2 - layer) << 8) + abs(0xF - (g_FrameCount & 0x1F));

    GFX_ADD_LAYER_DRAW_MODE(GFX_LAYER_FIELD_SCENE, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256));

    row    = 0;
    quad   = g_ScratchPadVectors;
    z      = 0xB00;
    y_high = 0;
    x_high = 0;
    top    = y - size;
    left   = x - size;
    do {
        prim = (POLY_FT4*)g_GfxPrimCursor;
        row++;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        quad[0].vx                = left;
        g_ScratchPadVectors[0].vy = top;
        g_ScratchPadVectors[0].vz = z;
        quad[1].vy                = top;
        quad[1].vz                = z;
        quad[2].vx                = left;
        quad[3].vx = quad[1].vx = x + size + x_high;
        quad[2].vz              = z;
        quad[3].vz              = z;
        quad[2].vy              = y + size + y_high;
        quad[3].vy              = y + size + y_high;
        RotTransPers4(&quad[0], &quad[1], &quad[2], &quad[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
        Area_ApplyTileToQuad(layer | AREA167_EFFECT_PART_WORD, prim, 1);
        GFX_AddPrim(GFX_LAYER_FIELD_SCENE, sizeof(POLY_FT4));
        top += 0x180;
        y_high += 0x180;
        left += 0xA00;
        x_high += 0xA00;
    } while (row < 3);
}
#else
INCLUDE_ASM(func_801F39BC);
#endif

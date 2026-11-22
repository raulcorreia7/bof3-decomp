#include "area167_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F39BC(void) {
    POLY_FT4* prim;
    SVECTOR*  quad;
    SVECTOR*  q1;
    SVECTOR*  q2;
    SVECTOR*  q3;
    long      depth;
    long      flag;
    s32       layer;
    s32       size;
    s32       x_high;
    s32       y_high;
    s32       x_left;
    s32       x_right;
    s32       y_left;
    s32       y_right;
    s32       x_step;
    s32       y_step;
    s32       i;

    layer = TASK(Actor)->param.unk_0B - 0x4B;
    if (TASK(Actor)->header.step == 0) {
        TASK(Actor)->vy = (layer * 0x600) + 0xC00 + (rand() & 0xFF);
        TASK(Actor)->screen_x = D_801F4A68[0x5C + ((COORD_FRAC(TASK(Actor)->pos.x) == 0) ? 2 : 0)];
        TASK(Actor)->screen_y = D_801F4A68[0x5D + ((COORD_FRAC(TASK(Actor)->pos.x) == 0) ? 2 : 0)];
        COORD_INT(TASK(Actor)->pos.y) += rand() & 7;
        TASK(Actor)->header.step++;
    }
    if ((g_AreaDrawFlags & AREA_DRAW_CELL_LAYERS) == 0) {
        return;
    }

    TASK(Actor)->pos.y.fixed += TASK(Actor)->vy;
    if ((s16)TASK(Actor)->screen_y < COORD_INT(TASK(Actor)->pos.y)) {
        COORD_INT(TASK(Actor)->pos.y) = TASK(Actor)->screen_x;
    }

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256), 0);
    GFX_AddPrim(GFX_LAYER_FIELD_SCENE, sizeof(DR_MODE));

    size    = ((2 - layer) << 8) + abs(0xF - (g_FrameCount & 0x1F));
    x_high  = (TASK(Actor)->pos.x.fixed >> 9) - 0x4EC0;
    y_high  = (TASK(Actor)->pos.y.fixed >> 9) - 0x3FC0;
    x_left  = x_high - size;
    x_right = x_high + size;
    y_left  = y_high - size;
    y_right = y_high + size;
    x_step  = 0;
    y_step  = 0;
    quad    = g_ScratchPadVectors;
    q1      = quad + 1;
    q2      = quad + 2;
    q3      = quad + 3;
    for (i = 0; i < 3; i++) {
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        quad->vx = x_left + x_step;
        quad->vy = y_left + y_step;
        quad->vz = 0xB00;
        q1->vx   = x_right + x_step;
        q1->vy   = y_left + y_step;
        q1->vz   = 0xB00;
        q2->vx   = x_left + x_step;
        q2->vy   = y_right + y_step;
        q2->vz   = 0xB00;
        q3->vx   = x_right + x_step;
        q3->vy   = y_right + y_step;
        q3->vz   = 0xB00;
        RotTransPers4(quad, q1, q2, q3, (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
        Area_ApplyTileToQuad(layer | 0xBB509100, prim, 1);
        GFX_AddPrim(GFX_LAYER_FIELD_SCENE, sizeof(POLY_FT4));
        x_step += 0xA00;
        y_step += 0x180;
    }
}
#else
INCLUDE_ASM(func_801F39BC);
#endif

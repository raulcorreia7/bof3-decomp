#include "area104_14.h"
#include "overlays/area/shared/world_cloud.h"

#define WORLD_CLOUD_BRIGHT_PART_WORD ((0xBB28u << 16) | 0xA100u)
#define WORLD_CLOUD_DIM_PART_WORD    ((0xBB50u << 16) | 0x9100u)

MATCH void func_801F4238(void) {
    POLY_FT4* prim;
    SVECTOR*  quad;
    SVECTOR*  q1;
    SVECTOR*  q2;
    SVECTOR*  q3;
    long      depth;
    long      flag;
    s32       width;
    s32       base_size;
    s32       size;
    s32       x_high;
    s32       y_high;

    if (g_Task->header.step == 0) {
        COORD_INT(g_Task->pos.y) += g_FrameCount & 0xF;
        g_Task->header.step++;
    }
    if ((g_AreaDrawFlags & AREA_DRAW_CELL_LAYERS) == 0) {
        return;
    }

    width = g_Task->param.cloud_layer - 2;
    g_Task->pos.y.fixed += 0x800 + (width << 10);
    if (g_AreaMapBundle.height + 8 < COORD_INT(g_Task->pos.y)) {
        COORD_INT(g_Task->pos.y) = -8;
    }

    if (abs(g_AreaTargetCellX - COORD_INT(g_Task->pos.x)) >= WORLDMAP_CLOUD_DRAW_RANGE && abs(g_AreaTargetCellY - COORD_INT(g_Task->pos.y)) >= WORLDMAP_CLOUD_DRAW_RANGE) {
        return;
    }

    prim   = (POLY_FT4*)g_GfxPrimCursor;
    x_high = (g_Task->pos.x.fixed >> 9) - (AREA_CELL_ORIGIN - AREA_CELL_HALF);
    y_high = (g_Task->pos.y.fixed >> 9) - (AREA_CELL_ORIGIN - AREA_CELL_HALF);
    SetPolyFT4(prim);
    SetShadeTex(prim, 0);
    quad      = g_ScratchPadVectors;
    q1        = quad + 1;
    q2        = quad + 2;
    q3        = quad + 3;
    base_size = (2 - width) << 8;
    size      = base_size;
    quad->vx  = x_high - size;
    quad->vy  = y_high - size;
    quad->vz  = 0;
    q1->vx    = x_high + size;
    q1->vy    = y_high - size;
    q1->vz    = 0;
    q2->vx    = x_high - size;
    q2->vy    = y_high + size;
    q2->vz    = 0;
    q3->vx    = x_high + size;
    q3->vy    = y_high + size;
    q3->vz    = 0;
    RotTransPers4(quad, q1, q2, q3, (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
    Area_ApplyTileToQuad(width | WORLD_CLOUD_BRIGHT_PART_WORD, prim, 1);
    GFX_AddPrim(5, sizeof(POLY_FT4));

    prim = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    SetShadeTex(prim, 0);
    size     = base_size + abs(0xF - (g_FrameCount & 0x1F));
    quad->vx = x_high - size;
    quad->vy = y_high - size;
    quad->vz = WORLD_CLOUD_DEPTH;
    q1->vx   = x_high + size;
    q1->vy   = y_high - size;
    q1->vz   = WORLD_CLOUD_DEPTH;
    q2->vx   = x_high - size;
    q2->vy   = y_high + size;
    q2->vz   = WORLD_CLOUD_DEPTH;
    q3->vx   = x_high + size;
    q3->vy   = y_high + size;
    q3->vz   = WORLD_CLOUD_DEPTH;
    RotTransPers4(quad, q1, q2, q3, (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
    Area_ApplyTileToQuad(width | WORLD_CLOUD_DIM_PART_WORD, prim, 1);
    GFX_AddPrim(4, sizeof(POLY_FT4));
}

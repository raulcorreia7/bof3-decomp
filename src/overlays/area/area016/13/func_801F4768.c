#include "area016_13.h"
#include "overlays/area/shared/world_cloud.h"

/* FAKE: the vertex stores cast to s16 inline to keep retail's add order. CLEANUP: name the vertex fields. */
MATCH void func_801F4768(void) {
    POLY_FT4* prim;
    POLY_FT4* cell;
    SVECTOR*  quad;
    SVECTOR*  q1;
    SVECTOR*  q2;
    SVECTOR*  q3;
    long      depth;
    long      flag;
    s32       width;
    s32       size;
    s32       row;
    s32       col;
    s32       x_high;
    s32       y_high;

    if (SELF(Actor)->header.step == 0) {
        COORD_INT(SELF(Actor)->pos.y) += g_FrameCount & 0xF;
        SELF(Actor)->header.step++;
    }
    if ((g_AreaDrawFlags & AREA_DRAW_CELL_LAYERS) == 0) {
        return;
    }

    width = SELF(Actor)->param.cloud_layer - 2;
    SELF(Actor)->pos.y.fixed += 0x800 + (width << 10);
    if (g_AreaMapBundle.height + 8 < COORD_INT(SELF(Actor)->pos.y)) {
        COORD_INT(SELF(Actor)->pos.y) = -8;
    }

    if (abs(g_AreaCamera.scroll_x.part.integer - COORD_INT(SELF(Actor)->pos.x)) >= 0x1A && abs(g_AreaCamera.scroll_y.part.integer - COORD_INT(SELF(Actor)->pos.y)) >= 0x1A) {
        return;
    }

    prim = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    SetShadeTex(prim, 0);
    quad     = g_ScratchPadVectors;
    q1       = quad + 1;
    q2       = quad + 2;
    q3       = quad + 3;
    size     = ((2 - width) << 8) + abs(0xF - (g_FrameCount & 0x1F));
    x_high   = (SELF(Actor)->pos.x.fixed >> 9) - (AREA_CELL_ORIGIN - AREA_CELL_HALF);
    y_high   = (SELF(Actor)->pos.y.fixed >> 9) - (AREA_CELL_ORIGIN - AREA_CELL_HALF);
    quad->vz = WORLD_CLOUD_DEPTH;
    q1->vz   = WORLD_CLOUD_DEPTH;
    q2->vz   = WORLD_CLOUD_DEPTH;
    q3->vz   = WORLD_CLOUD_DEPTH;
    quad->vx = x_high - size;
    quad->vy = y_high - size;
    q1->vx   = x_high + size;
    q1->vy   = y_high - size;
    q2->vx   = x_high - size;
    q2->vy   = y_high + size;
    q3->vx   = x_high + size;
    q3->vy   = y_high + size;
    RotTransPers4(quad, q1, q2, q3, (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
    Area_ApplyTileToQuad(width | 0xBB509100, prim, 1);
    GFX_AddPrim(GFX_LAYER_BATTLE_SCENE, sizeof(POLY_FT4));

    for (row = 0; row < (2 - width) * 4 + 1; row++) {
        for (col = 0; col < (2 - width) * 4; col++) {
            cell = Area_CellFindQuad(COORD_INT(SELF(Actor)->pos.x) - (2 - width) + col, COORD_INT(SELF(Actor)->pos.y) - (2 - width) + row);
            if (cell == NULL) {
                continue;
            }
            prim = (POLY_FT4*)g_GfxPrimCursor;
            SetPolyFT4(prim);
            SetShadeTex(prim, 0);
            PSX_SET_SEMI_TRANSPARENT(prim);
            *(u32*)&prim->x0 = *(u32*)&cell->x0;
            *(u32*)&prim->x1 = *(u32*)&cell->x1;
            *(u32*)&prim->x2 = *(u32*)&cell->x2;
            *(u32*)&prim->x3 = *(u32*)&cell->x3;
            prim->clut       = getClut(176, 483);
            prim->tpage      = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, 704, 256);
            setRGB0(prim, 40, 40, 40);
            setUV4(prim, D_801F51D8[width] + col * D_801F51E0[width], D_801F51DC[width] + row * D_801F51E0[width] - D_801F51E0[width] * COORD_FRAC(SELF(Actor)->pos.y) / 0x10000,
                   D_801F51E0[width] + (D_801F51D8[width] + D_801F51E0[width] * col), D_801F51DC[width] + row * D_801F51E0[width] - D_801F51E0[width] * COORD_FRAC(SELF(Actor)->pos.y) / 0x10000,
                   D_801F51D8[width] + col * D_801F51E0[width], D_801F51E0[width] + (u8)(D_801F51DC[width] + row * D_801F51E0[width] - D_801F51E0[width] * COORD_FRAC(SELF(Actor)->pos.y) / 0x10000),
                   D_801F51E0[width] + (D_801F51D8[width] + D_801F51E0[width] * col),
                   D_801F51E0[width] + (u8)(D_801F51DC[width] + row * D_801F51E0[width] - D_801F51E0[width] * COORD_FRAC(SELF(Actor)->pos.y) / 0x10000));
            Area_CellAddPrim((COORD_INT(SELF(Actor)->pos.x) - (2 - width) + col) << 16, (COORD_INT(SELF(Actor)->pos.y) - (2 - width) + row) << 16, 1, 0x28);
        }
    }
}

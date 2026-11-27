#include "area106_13.h"

/* Draws four textured quads at the current tilt. */
MATCH void func_801F2F38(s32 index, s32 height) {
    SVECTOR   pos;
    SVECTOR   rot;
    MATRIX    matrix;
    long      flag;
    long      depth;
    POLY_FT4* prim;
    u8*       first_tile;
    u8*       tile_table;
    s32       tile_offset;
    u8*       tile;
    s32       vertex;
    SVECTOR*  corner;
    void*     xy0;
    void*     xy1;
    void*     xy2;
    void*     xy3;

    GFX_ADD_LAYER_DRAW_MODE(GFX_LAYER_SCENE_BACK, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256));

    /* FAKE: keeps the tilt ahead of the tile base in register allocation (23 rows with plain C). */
    do {
        rot.vy = -height;
    } while (0);
    pos.vx = -0x37C0;
    pos.vy = -0x2DC0;
    rot.vz = 0;
    rot.vx = 0;
    pos.vz = -0x480;

    PushMatrix();
    RotTransMatrix(&pos, matrix, &flag);
    RotMatrix(&rot, &matrix);
    MulMatrix2(&g_CameraMatrix, &matrix);
    SetRotMatrix(&matrix);
    tile_table = D_801F3F18;
    SetTransMatrix(&matrix);

    tile_offset = index * 4;
    first_tile  = tile_table + tile_offset;
    tile        = first_tile;
next_tile:
    {
        prim = GFX_CURSOR(POLY_FT4);
        /* FAKE: keeps the primitive pointer ahead of the tile cursor in register allocation (23 rows with plain C). */
        do {
            SetPolyFT4(prim);
            SetShadeTex(prim, 0);
        } while (0);
        for (vertex = 0; vertex < 4; vertex++) {
            g_ScratchPadVectors[vertex].vx = D_801F3EE8[*tile][vertex].x << 7;
            g_ScratchPadVectors[vertex].vy = D_801F3EE8[*tile][vertex].y << 7;
            g_ScratchPadVectors[vertex].vz = -D_801F3EE8[*tile][vertex].depth << 7;
        }
        corner = g_ScratchPadVectors;
        xy0    = &prim->x0;
        xy1    = &prim->x1;
        xy2    = &prim->x2;
        xy3    = &prim->x3;
        RotTransPers4(corner, &corner[1], &corner[2], &corner[3], xy0, xy1, xy2, xy3, &depth, &flag);
        Area_ApplyTileToQuad(D_801F3F20[*tile] + (((height * D_801F3F30[*tile]) << 8) & AREA106_TILE_WORD_MASK), prim, 1);
        GFX_AddPrim(GFX_LAYER_SCENE_BACK, sizeof(POLY_FT4));
    }
    if ((s32)++tile < (s32)(first_tile + 4)) {
        goto next_tile;
    }
    PopMatrix();
}

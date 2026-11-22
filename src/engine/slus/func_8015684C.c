#include "engine/slus/slus.h"

/* builds the projected quad for one map cell's texture entry, stages
 * the primitive, and appends it to the ordering table.
 */
MATCH void func_8015684C(u32* record, s32 cell_x, s32 cell_y) {
    AreaCellCorners* cell;
    AreaCellCorners* row;
    POLY_FT4*        prim;
    SVECTOR*         vert;
    SVECTOR          v[4];
    u16              flag;
    s32              p;
    s32              x;
    s32              y;
    u16              y_edge;
    s32              z;
    u8               state;

    if ((*record >> 0x1C) != 0) {
        state = GFX_LAYER_FIELD_SCENE;
    } else {
        state = g_AreaDrawMode;
    }
    row     = (AreaCellCorners*)(MAP_BUNDLE_BASE + 0x30) + cell_y * g_AreaMapBundle.width;
    cell    = (AreaCellCorners*)(cell_x * 4 + (u32)row);
    x       = (cell_x - 128) << 7;
    v[0].vx = v[2].vx = x - AREA_CELL_HALF;
    prim              = (POLY_FT4*)g_GfxPrimCursor;
    y                 = (cell_y - 128) << 7;
    y_edge            = y - AREA_CELL_HALF;
    v[0].vy = v[2].vy = y | AREA_CELL_HALF;
    z                 = cell->corner_pair[1];
    v[1].vx = v[3].vx = x | AREA_CELL_HALF;
    v[1].vy = v[3].vy = y_edge;
    z                 = -((z & BYTE_MASK) << 4);
    vert              = &v[0];
    v[2].vz           = z;
    v[0].vz           = z - 128;
    z                 = -((u8)cell->corner_height[1] << 4);
    v[3].vz           = z;
    v[1].vz           = z - 128;
    SetPolyFT4(prim);
    SetShadeTex(prim, 0);
    RotTransPers4(vert, &v[1], &v[2], &v[3], (s32*)&prim->x0, (s32*)&prim->x1, (s32*)&prim->x2, (s32*)&prim->x3, &p, &flag);
    Area_ApplyTileToQuad(0xB1800110u, prim, 1);
    GFX_AddPrim(state, sizeof(POLY_FT4));
}

#include "engine/slus/slus.h"

/* builds the projected quad for one map cell's texture entry, stages
 * the primitive, and appends it to the ordering table.
 */
MATCH void func_8015684C(u32* record, s32 cell_x, s32 cell_y) {
    AreaCellCorners* cell;
    AreaCellCorners* row;
    u8*              prim;
    SVECTOR*         vert;
    SVECTOR          v0;
    SVECTOR          v1;
    SVECTOR          v2;
    SVECTOR          v3;
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
    row   = (AreaCellCorners*)(MAP_BUNDLE_BASE + 0x30) + cell_y * g_AreaMapBundle.width;
    cell  = (AreaCellCorners*)(cell_x * 4 + (u32)row);
    x     = (cell_x - 128) << 7;
    v0.vx = v2.vx = x - AREA_CELL_HALF;
    prim          = g_GfxPrimCursor;
    y             = (cell_y - 128) << 7;
    y_edge        = y - AREA_CELL_HALF;
    v0.vy = v2.vy = y | AREA_CELL_HALF;
    z             = cell->corner_pair[1];
    v1.vx = v3.vx = x | AREA_CELL_HALF;
    v1.vy = v3.vy = y_edge;
    z             = -((z & BYTE_MASK) << 4);
    vert          = &v0;
    v2.vz         = z;
    v0.vz         = z - 128;
    z             = -((u8)cell->corner_height[1] << 4);
    v3.vz         = z;
    v1.vz         = z - 128;
    SetPolyFT4((POLY_FT4*)prim);
    SetShadeTex(prim, 0);
    RotTransPers4(vert, &v1, &v2, &v3, (s32*)(prim + 8), (s32*)(prim + 0x10), (s32*)(prim + 0x18), (s32*)(prim + 0x20), &p, &flag);
    Area_ApplyTileToQuad(0xB1800110u, prim, 1);
    GFX_AddPrim(state, sizeof(POLY_FT4));
}

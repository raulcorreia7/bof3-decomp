#include "engine/slus/slus.h"

typedef struct {
    u8  unk_00;
    u8  unk_01;
    u16 unk_02;
} MapCell;

/* builds the projected quad for one map cell's texture entry, stages
 * the primitive, and appends it to the ordering table.
 */
#ifdef NON_MATCHING
NON_MATCHING void func_8015684C(u8* record, s32 cell_x, s32 cell_y) {
    MapCell* cell;
    u8*      prim;
    SVECTOR  v0;
    SVECTOR  v1;
    SVECTOR  v2;
    SVECTOR  v3;
    s32      p;
    s32      flag;
    s32      x;
    s32      y;
    s32      z;
    s32      edge;
    u8       state;

    if ((*(u32*)record >> 0x1C) != 0) {
        state = 6;
    } else {
        state = g_AreaDrawMode;
    }
    cell  = ((MapCell*)(MAP_BUNDLE_BASE + 0x30) + cell_y * g_AreaMapBundle.width) + cell_x;
    x     = (cell_x - 128) << 7;
    edge  = x - 64;
    v0.vx = v2.vx = edge;
    prim          = g_GfxPrimCursor;
    y             = (cell_y - 128) << 7;
    edge          = y - 64;
    y |= 64;
    v0.vy = v2.vy = y;
    z             = cell->unk_02;
    x |= 64;
    v1.vx = v3.vx = x;
    v1.vy = v3.vy = edge;
    z             = -((z & BYTE_MASK) << 4);
    v2.vz         = z;
    v0.vz         = z - 128;
    z             = -(cell->unk_01 << 4);
    v3.vz         = z;
    v1.vz         = z - 128;
    SetPolyFT4((POLY_FT4*)prim);
    SetShadeTex(prim, 0);
    RotTransPers4(&v0, &v1, &v2, &v3, (s32*)(prim + 8), (s32*)(prim + 0x10), (s32*)(prim + 0x18), (s32*)(prim + 0x20), &p, &flag);
    func_80155560(0xB1800110u, prim, 1);
    GFX_AddPrim(state, sizeof(POLY_FT4));
}
#else
INCLUDE_ASM(func_8015684C);
#endif

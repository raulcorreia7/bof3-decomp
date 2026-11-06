#include "engine/slus/slus.h"

typedef struct {
    u8  unk_00;
    u8  unk_01;
    u16 unk_02;
} MapCell;

/* builds the projected quad for one map cell's texture entry, stages
 * the primitive, and appends it to the ordering table.
 */
/* nonmatching unmeasured: tried the first draft cleaned to compiling C; register pins dropped, score is the pinned draft; best
 * score 77.33%. resume: a lever or header fix that closes the first mismatch. */
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
    s32      t1;
    s32      t2;
    s32      z0;
    s32      z1;
    u8       state;
    s32      ay;
    s32      x0;
    s32      x1;
    s32      y0;
    s32      y1;

    ay = cell_y;
    if ((*(u32*)record >> 0x1C) != 0) {
        state = 6;
    } else {
        state = g_AreaDrawMode;
    }
    t1    = (cell_x - 0x80) << 7;
    x0    = t1 - 0x40;
    v2.vx = x0;
    v0.vx = x0;
    prim  = g_GfxPrimCursor;
    t2    = (ay - 0x80) << 7;
    y1    = t2 - 0x40;
    y0    = t2 | 0x40;
    v2.vy = y0;
    v0.vy = y0;
    cell  = (MapCell*)((cell_x * 4) + ((ay * g_AreaMapBundle.width_00 * 4) + (MAP_BUNDLE_BASE + 0x30)));
    x1    = t1 | 0x40;
    v3.vx = x1;
    v1.vx = x1;
    v3.vy = y1;
    v1.vy = y1;
    z0    = -((cell->step & 0xFF) << 4);
    v2.vz = z0;
    v0.vz = z0 - 0x80;
    z1    = -(cell->mode << 4);
    v3.vz = z1;
    v1.vz = z1 - 0x80;
    SetPolyFT4((POLY_FT4*)prim);
    SetShadeTex(prim, 0);
    RotTransPers4(&v0, &v1, &v2, &v3, (s32*)(prim + 8), (s32*)(prim + 0x10), (s32*)(prim + 0x18), (s32*)(prim + 0x20),
                  &p, &flag);
    func_80155560(0xB1800110u, prim, 1);
    GFX_AddPrim(state, 0x28);
}
#else
INCLUDE_ASM(func_8015684C);
#endif

#include "engine/slus/slus.h"

/* The four signed height bytes of a map cell word. */
#define CELL_H0(word) (((word) << 24) >> 24)
#define CELL_H1(word) (((word) << 16) >> 24)
#define CELL_H2(word) (((word) << 8) >> 24)
#define CELL_H3(word) ((word) >> 24)

/* Draws the wall quads between a map cell and its left or upper neighbour; the record's byte 3 picks one side or both. */
MATCH void func_80157CE4(u8* record, s32 cell_x, s32 cell_y) {
    SVECTOR v0;
    SVECTOR v1;
    SVECTOR v2;
    SVECTOR v3;
    s32     p;
    s32     flag;
    s32*    cell;
    s32*    other;
    s32*    row;
    u8*     prim;
    s32     count;
    s32     side;
    s32     kind;

    kind = (u32)(record[3] - 63) >> 1;
    if (kind < 4) {
        count = 1;
        side  = kind;
    } else {
        count = 2;
        side  = (kind - 4) * 2;
    }
    row    = (s32*)(MAP_BUNDLE_BASE + 0x30) + cell_y * g_AreaMapBundle.width;
    cell   = (s32*)(cell_x * 4 + (u32)row);
    cell_x = ((cell_x - 128) << 7) - 64;
    v0.vx = v2.vx = cell_x;
    cell_y        = ((cell_y - 128) << 7) - 64;
    v0.vy = v2.vy = cell_y;
    while (count > 0) {
        prim = g_GfxPrimCursor;
        SetPolyFT4((POLY_FT4*)prim);
        SetShadeTex(prim, 0);
        v1.vx = v3.vx = (side & 1) ? cell_x : cell_x + 128;
        v1.vy = v3.vy = cell_y + ((side & 1) << 7);
        if (side & 1) {
            if ((CELL_H0(cell[0]) < CELL_H1(cell[-1])) || (CELL_H3(cell[-1]) > CELL_H2(cell[0]))) {
                v2.vz = -(CELL_H1(cell[-1]) << 4);
                v3.vz = -(CELL_H3(cell[-1]) << 4);
            } else {
                v2.vz = -(CELL_H0(cell[0]) << 4);
                v3.vz = -((s8)((u16*)cell)[1] << 4);
            }
        } else {
            other = cell - g_AreaMapBundle.width;
            if ((CELL_H0(cell[0]) < CELL_H2(other[0])) || (CELL_H3(other[0]) > CELL_H1(cell[0]))) {
                v2.vz = -(CELL_H2(other[0]) << 4);
                v3.vz = -((s8)((u8*)other)[3] << 4);
            } else {
                v2.vz = -(CELL_H0(cell[0]) << 4);
                v3.vz = -(CELL_H1(cell[0]) << 4);
            }
        }
        v0.vz = v2.vz - 128;
        v1.vz = v3.vz - 128;
        RotTransPers4(&v0, &v1, &v2, &v3, (s32*)(prim + 8), (s32*)(prim + 0x10), (s32*)(prim + 0x18), (s32*)(prim + 0x20), &p, &flag);
        count--;
        func_80155560(D_8017F8E0[side], prim, 1);
        side++;
        GFX_AddPrim(g_AreaDrawMode, sizeof(POLY_FT4));
    }
}

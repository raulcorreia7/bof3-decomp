#include "engine/slus/slus.h"

/* One map cell: four height bytes, read as a word, as its upper half or by byte. */
typedef union MapCellHeights {
    s32 word;
    u16 halves[2];
    u8  bytes[4];
} MapCellHeights;

/* The signed height of corner 0 to 3 of a map cell word: one byte each, corner 0 lowest. */
#define MAP_CELL_CORNER_HEIGHT(word, corner) (((word) << (3 - (corner)) * BYTE_WIDTH) >> 3 * BYTE_WIDTH)

/* Draws the wall quads between a map cell and its left or upper neighbour; the record's byte 3 picks one side or both. */
MATCH void Area_DrawCellSides(u8* record, s32 cell_x, s32 cell_y) {
    SVECTOR         v[4];
    s32             p;
    s32             flag;
    MapCellHeights* cell;
    MapCellHeights* other;
    MapCellHeights* row;
    u8*             prim;
    s32             count;
    s32             side;
    s32             type;

    type = (u32)(record[3] - 63) >> 1;
    if (type < 4) {
        count = 1;
        side  = type;
    } else {
        count = 2;
        side  = (type - 4) * 2;
    }
    row     = (MapCellHeights*)(MAP_BUNDLE_BASE + 0x30) + cell_y * g_AreaMapBundle.width;
    cell    = (MapCellHeights*)(cell_x * 4 + (u32)row);
    cell_x  = ((cell_x - 128) << 7) - 64;
    v[0].vx = v[2].vx = cell_x;
    cell_y            = ((cell_y - 128) << 7) - 64;
    v[0].vy = v[2].vy = cell_y;
    while (count > 0) {
        prim = g_GfxPrimCursor;
        SetPolyFT4((POLY_FT4*)prim);
        SetShadeTex(prim, 0);
        v[1].vx = v[3].vx = (side & 1) ? cell_x : cell_x + 128;
        v[1].vy = v[3].vy = cell_y + ((side & 1) << 7);
        if (side & 1) {
            if ((MAP_CELL_CORNER_HEIGHT(cell[0].word, 0) < MAP_CELL_CORNER_HEIGHT(cell[-1].word, 1)) || (MAP_CELL_CORNER_HEIGHT(cell[-1].word, 3) > MAP_CELL_CORNER_HEIGHT(cell[0].word, 2))) {
                v[2].vz = -(MAP_CELL_CORNER_HEIGHT(cell[-1].word, 1) << 4);
                v[3].vz = -(MAP_CELL_CORNER_HEIGHT(cell[-1].word, 3) << 4);
            } else {
                v[2].vz = -(MAP_CELL_CORNER_HEIGHT(cell[0].word, 0) << 4);
                v[3].vz = -((s8)cell->halves[1] << 4);
            }
        } else {
            other = cell - g_AreaMapBundle.width;
            if ((MAP_CELL_CORNER_HEIGHT(cell[0].word, 0) < MAP_CELL_CORNER_HEIGHT(other[0].word, 2)) || (MAP_CELL_CORNER_HEIGHT(other[0].word, 3) > MAP_CELL_CORNER_HEIGHT(cell[0].word, 1))) {
                v[2].vz = -(MAP_CELL_CORNER_HEIGHT(other[0].word, 2) << 4);
                v[3].vz = -((s8)other->bytes[3] << 4);
            } else {
                v[2].vz = -(MAP_CELL_CORNER_HEIGHT(cell[0].word, 0) << 4);
                v[3].vz = -(MAP_CELL_CORNER_HEIGHT(cell[0].word, 1) << 4);
            }
        }
        v[0].vz = v[2].vz - 128;
        v[1].vz = v[3].vz - 128;
        RotTransPers4(&v[0], &v[1], &v[2], &v[3], (s32*)(prim + 8), (s32*)(prim + 0x10), (s32*)(prim + 0x18), (s32*)(prim + 0x20), &p, &flag);
        count--;
        Area_ApplyTileToQuad(D_8017F8E0[side], prim, 1);
        side++;
        GFX_AddPrim(g_AreaDrawMode, sizeof(POLY_FT4));
    }
}

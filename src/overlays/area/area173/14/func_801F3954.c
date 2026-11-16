#include "area173_14.h"

/* Draws one sweep frame: each cell row builds an FT4 quad from the four vertex cells around its
 * cell pair, projects the quad and stages the cell origin for the sprite pass. */
#ifdef NON_MATCHING
NON_MATCHING void func_801F3954(s32 frame) {
    POLY_FT4* prim;
    u16*      slot;
    u8*       cell_x;
    u8*       cell_y;
    s32       start;
    s32       row;
    s32       entry;
    s32       offset;
    s32       i;
    long      depth;
    long      flag;

    start = D_801F52E8[frame][0];
    if (start >= D_801F52E9[frame][0]) {
        return;
    }
    slot   = D_1F800034_U16;
    cell_y = D_801F4F15 + start * 20;
    cell_x = D_801F4F15 + start * 20 - 1;
    row    = start * 20;
    while (start < D_801F52E9[frame][0]) {
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        slot[0] = ((*cell_x) << 7) - (AREA_CELL_ORIGIN + AREA_CELL_HALF);
        slot[1] = ((*cell_y) << 7) - (AREA_CELL_ORIGIN + AREA_CELL_HALF);
        i       = 0;
        entry   = row;
        offset  = 0;
        do {
            i++;
            FIELD(u16, D_1F800014, offset)     = (slot[0] + D_801F4F16[entry] * 64) + slot[2];
            FIELD(u16, D_1F800014, offset + 2) = slot[1] + D_801F4F17[entry] * 64;
            FIELD(u16, D_1F800014, offset + 4) = (slot[3] + 0x180) - D_801F4F18[entry] * 64;
            offset += 8;
            entry += 3;
        } while (i < 4);
        RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
        func_80155560(LOWU(D_801F4F24[row]), prim, 1);
        row += 20;
        Area_AddCellPrim(((*cell_x) << 16) + (D_1F800038 << 9), (*cell_y) << 16, 0, sizeof(POLY_FT4));
        cell_y += 20;
        cell_x += 20;
        start++;
    }
}
#else
INCLUDE_ASM(func_801F3954);
#endif

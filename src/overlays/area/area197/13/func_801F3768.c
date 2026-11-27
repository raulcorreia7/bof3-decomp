#include "area197_13.h"

/* Draws a pulsing textured square on every other cell of columns 3..13, rows 0x71..0x76. */
MATCH void func_801F3768(s32 shade, s32 rise) {
    POLY_FT4* prim;
    s32       row;
    s32       col;
    s32       size;
    long      depth;
    long      flag;
    s32       cell_x;
    s32       cell_y;
    s32       u;

    for (row = 0x71; row < 0x77; row++) {
        for (col = 3; col < 14; col++) {
            if ((row + col) & 1) {
                continue;
            }
            SPAD(0u)->vectors[0].vx = (col - 0x80) << 7;
            SPAD(0u)->vectors[0].vy = ((row - 0x80) << 7) - rise * 2;
            SPAD(0u)->vectors[0].vz = ((row - 0x80) << 4) + 0x90;
            RotTransPers(g_ScratchPadVectors, (long*)D_1F800034, &depth, &flag);
            prim = (POLY_FT4*)g_GfxPrimCursor;
            size = abs(3 - ((g_FrameCount / 3 + (row + col)) & 7)) + 0x18;
            SetPolyFT4(prim);
            SetShadeTex(prim, 0);
            setXYWH(prim, D_1F800034[0] - size, D_1F800034[1] - size, size * 2, size * 2);
            SetSemiTrans(prim, 1);
            u = 0xE0;
            setUVWH(prim, u, 0x30, 0x1F, 0x1F);
            cell_x      = TO_COORD(col);
            cell_y      = TO_COORD(row);
            prim->tpage = getTPage(0, 1, 0x2C0, 0x100);
            prim->clut  = 0x78CA;
            setRGB0(prim, shade / 2, shade, shade / 2);
            Area_CellAddPrim(cell_x, cell_y, 1, sizeof(POLY_FT4));
        }
    }
}

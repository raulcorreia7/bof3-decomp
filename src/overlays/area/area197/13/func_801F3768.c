#include "area197_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3768(s32 shade, s32 rise) {
    /* FAKE: retail reserves 0x10 frame bytes above the rise spill slot; this pad sits below the locals. */
    FAKE_STACK_PADS(u8, 0x10);
    POLY_FT4* prim;
    s32       row;
    s32       col;
    s32       size;
    s32       depth_z;
    long      depth;
    long      flag;
    s32       cell_x;
    s32       cell_y;

    for (row = 0x71, depth_z = -0x60; row < 0x77; depth_z += 0x10, row++) {
        for (col = 3; col < 14; col++) {
            if ((row + col) & 1) {
                continue;
            }
            SPAD(0u)->vectors[0].vx = (col - 0x80) << 7;
            SPAD(0u)->vectors[0].vy = ((row - 0x80) << 7) - rise * 2;
            SPAD(0u)->vectors[0].vz = depth_z;
            RotTransPers(g_ScratchPadVectors, (long*)D_1F800034, &depth, &flag);
            prim = (POLY_FT4*)g_GfxPrimCursor;
            size = abs(3 - ((g_FrameCount / 3 + (row + col)) & 7)) + 0x18;
            SetPolyFT4(prim);
            SetShadeTex(prim, 0);
            setXY4(prim, D_1F800034[0] - size, D_1F800034[1] - size, D_1F800034[0] + size, D_1F800034[1] - size, D_1F800034[0] - size, D_1F800034[1] + size, D_1F800034[0] + size,
                   D_1F800034[1] + size);
            SetSemiTrans(prim, 1);
            setUV4(prim, 0xE0, 0x30, 0xFF, 0x30, 0xE0, 0x4F, 0xFF, 0x4F);
            cell_x      = TO_COORD(col);
            cell_y      = TO_COORD(row);
            prim->tpage = (GetGraphType() == 1 || GetGraphType() == 2) ? 0xAB : 0x3B;
            prim->clut  = 0x78CA;
            setRGB0(prim, shade / 2, shade, shade / 2);
            Area_CellAddPrim(cell_x, cell_y, 1, sizeof(POLY_FT4));
        }
    }
}
#else
INCLUDE_ASM(func_801F3768);
#endif

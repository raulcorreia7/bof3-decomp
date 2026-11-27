#include "area119_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F369C(s32 level) {
    POLY_FT4* prim;
    long      depth;
    long      flag;
    s32       i;
    s32       j;
    s32       phase;
    s32       row;
    s32       z;
    s32       size;
    s32       tilt;
    s32       x_lo;
    s32       x_hi;
    s32       y_lo;
    s32       y_hi;
    s32       band_y;

    /* three bands of eight quads: the pillar steps down a band and back a row at a time */
    for (i = 0, band_y = -0x2120; i < 3; i++, band_y += 0x60) {
        phase = g_FrameCount & 7;
        row   = phase;
        z     = -0x190 - phase * 8;
        for (j = 0; j < 8; j++) {
            prim = (POLY_FT4*)g_GfxPrimCursor;
            SetPolyFT4(prim);
            SetShadeTex(prim, 0);
            SetSemiTrans(prim, 1);

            /* the row's quad widens as the phase advances and leans with the band */
            size = phase * 2 + j * 16 + 0x18;
            tilt = rsin(row * 16) >> 5;
            x_lo = -0x1F40 - size + tilt;
            x_hi = -0x1F40 + size + tilt;
            y_lo = band_y - size + tilt * (i - 1);
            y_hi = band_y + size + tilt * (i - 1);
            setVector(&g_ScratchPadVectors[0], x_lo, y_lo, z);
            setVector(&g_ScratchPadVectors[1], x_hi, y_lo, z);
            setVector(&g_ScratchPadVectors[2], x_lo, y_hi, z);
            setVector(&g_ScratchPadVectors[3], x_hi, y_hi, z);
            RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                          &depth, &flag);

            setUV4(prim, 0xE0, 0x30, 0xFF, 0x30, 0xE0, 0x4F, 0xFF, 0x4F);
            prim->tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 704, 256);
            prim->clut  = getClut(160, 483);
            /* the band fades from its bottom row toward the top of the pillar */
            setRGB0(prim, (0x3F - row) * (level * 2) / 0x80, (0x3F - row) * level / 0x80, (0x3F - row) * (level * 2) / 0x80);
            GFX_AddPrim(4, sizeof(POLY_FT4));

            row += 8;
            z -= 0x40;
        }

        /* the band's own sprite, projected from one point behind the pillar */
        g_ScratchPadVectors[0].vx = -0x1F40;
        D_1F800016                = band_y;
        D_1F800018                = -0x1C0;
        RotTransPers(g_ScratchPadVectors, (long*)D_1F800034, &depth, &flag);

        size = abs(3 - ((g_FrameCount / 3 + i) & 7)) + 0x10;
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        setXY4(prim, (u16)D_1F800034[0] - size, (u16)D_1F800034[1] - size, (u16)D_1F800034[0] + size, (u16)D_1F800034[1] - size, (u16)D_1F800034[0] - size, (u16)D_1F800034[1] + size,
               (u16)D_1F800034[0] + size, (u16)D_1F800034[1] + size);
        SetSemiTrans(prim, 1);
        setUV4(prim, 0xE0, 0x30, 0xFF, 0x30, 0xE0, 0x4F, 0xFF, 0x4F);
        prim->tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 704, 256);
        prim->clut  = getClut(160, 483);
        setRGB0(prim, level * 0x60 / 0x80, level * 0x30 / 0x80, level * 0x60 / 0x80);
        {
            Coord cell_x = {TO_COORD(0x3F)};
            Coord cell_y = {TO_COORD(0x3D)};

            Area_CellAddPrim(cell_x.fixed, cell_y.fixed, 1, sizeof(POLY_FT4));
        }
    }
}
#else
INCLUDE_ASM(func_801F369C);
#endif

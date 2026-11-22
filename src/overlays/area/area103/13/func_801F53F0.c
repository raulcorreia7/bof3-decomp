#include "area103_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F53F0(s32 radius) {
    TILE_1* tile;
    s32     x;
    s32     y;
    s32     z;
    s32     scale;
    s32     shade;
    s32     alternate;
    s32     i;
    u16     tpage;
    long    depth;
    long    flag;

    x = (g_Task->pos.x.part.integer - 0x80) << 7;
    y = (g_Task->pos.y.part.integer - 0x80) << 7;
    z = -((s16)Area_SampleHeight(g_Task->pos.x.fixed, g_Task->pos.y.fixed) / 2);
    setVector(&g_ScratchPadVectors[0], x, y, z);
    RotTransPers(g_ScratchPadVectors, (long*)D_1F800034_U16, &depth, &flag);

    tpage = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, tpage, 0);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 1, sizeof(DR_MODE));

    scale     = radius << 2;
    shade     = scale ^ 0x3F;
    alternate = shade << 1;
    for (i = 0; i < 64; i++) {
        tile = (TILE_1*)g_GfxPrimCursor;
        SetTile1(tile);
        SetSemiTrans(tile, 1);
        tile->x0 = ((rsin(i << 7) * scale) >> 14) + D_1F800034_U16[0];
        setRGB0(tile, alternate, alternate * (g_FrameCount & 1), shade * (g_FrameCount & 1));
        tile->y0 = ((rcos(i << 7) * scale) >> 15) + 8 + D_1F800034_U16[1];
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));
    }
}
#else
INCLUDE_ASM(func_801F53F0);
#endif

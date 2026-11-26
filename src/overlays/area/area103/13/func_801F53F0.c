#include "area103_13.h"

/* Draws a ring of 64 flickering one-pixel tiles of the given radius around the actor's projected position. */
MATCH void func_801F53F0(s32 radius) {
    TILE_1* tile;
    s32     x;
    s32     y;
    s32     z;
    s32     shade;
    s32     alternate;
    s32     i;
    s32     offset;
    u16     tpage;
    long    depth;
    long    flag;

    x = (TASK(Actor)->pos.x.part.integer - 0x80) << 7;
    y = (TASK(Actor)->pos.y.part.integer - 0x80) << 7;
    z = (s16)Area_HeightSample(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed) / 2;
    z = -z;
    setVector(&g_ScratchPadVectors[0], x, y, z);
    RotTransPers(g_ScratchPadVectors, (long*)D_1F800034_U16, &depth, &flag);

    tpage = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, tpage, 0);
    Area_CellAddPrim(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed, 1, sizeof(DR_MODE));

    radius <<= 2;
    for (i = 0; i < 64; i++) {
        tile = (TILE_1*)g_GfxPrimCursor;
        SetTile1(tile);
        SetSemiTrans(tile, 1);
        tile->x0  = D_1F800034_U16[0] + ((rsin(i << 7) * radius) >> 14);
        offset    = ((rcos(i << 7) * radius) >> 15) + 8;
        tile->y0  = D_1F800034_U16[1] + offset;
        shade     = radius ^ 0x3F;
        alternate = shade << 1;
        setRGB0(tile, alternate, alternate * (g_FrameCount & 1), shade * (g_FrameCount & 1));
        Area_CellAddPrim(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed, 2, sizeof(DR_MODE));
    }
}

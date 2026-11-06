#include "area185_13.h"

MATCH void func_801F3474(void) {
    TILE_1* tile;
    s32     i;
    s32     j;
    s32     mode;
    s32     value;
    s32     angle;
    s32     p;
    s32     flag;

    D_1F800034[0] = -0x3100;
    D_1F800034[1] = -0x3A00;

    mode = getTPage(1, 1, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, mode, 0);
    Area_AddCellPrim(g_Task->x.fixed, g_Task->y.fixed, 1, 0xC);

    for (i = 0; i < 32; i++) {
        for (j = 0; j < 8; j++) {
            tile = (TILE_1*)g_GfxPrimCursor;
            SetTile1(tile);
            PSX_SET_SEMI_TRANSPARENT(tile);
            value = (0x17F - ((i << 3) + (g_FrameCount & 7))) >> 1;
            setRGB0(tile, value / 4, value / 4, value);

            angle            = 256 + j * ANGLE_45;
            D_1F800014[0].vx = D_1F800034[0] + (((rsin(angle) * ((i << 4) + (g_FrameCount & 0xF)) * 5)) >> 16);
            D_1F800014[0].vy = D_1F800034[1] + (((rcos(angle) * ((i << 4) + (g_FrameCount & 0xF)) * 5)) >> 16);
            D_1F800014[0].vz = -0x340 - (rsin(((i << 4) + (g_FrameCount & 0xF)) * 5) >> 5);
            RotTransPers(D_1F800014, (long*)&tile->x0, (long*)&p, (long*)&flag);

            Area_AddCellPrim(g_Task->x.fixed, g_Task->y.fixed, 1, 0xC);
        }
    }

    mode = getTPage(1, 1, 320, 256);
    GFX_SET_DRAW_MODE(mode);
    Area_AddCellPrim(g_Task->x.fixed, g_Task->y.fixed, 1, 0xC);
}

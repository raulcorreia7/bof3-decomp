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

    mode = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, mode, 0);
    Area_CellAddPrim(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, 1, sizeof(DR_MODE));

    for (i = 0; i < 32; i++) {
        for (j = 0; j < 8; j++) {
            tile = (TILE_1*)g_GfxPrimCursor;
            SetTile1(tile);
            PSX_SET_SEMI_TRANSPARENT(tile);
            value = (0x17F - ((i << 3) + (g_FrameCount & 0x7))) >> 1;
            setRGB0(tile, value / 4, value / 4, value);

            angle                     = 256 + j * ANGLE_45;
            g_ScratchPadVectors[0].vx = D_1F800034[0] + (((rsin(angle) * ((i << 4) + (g_FrameCount & 0xF)) * 5)) >> 16);
            g_ScratchPadVectors[0].vy = D_1F800034[1] + (((rcos(angle) * ((i << 4) + (g_FrameCount & 0xF)) * 5)) >> 16);
            g_ScratchPadVectors[0].vz = -0x340 - (rsin(((i << 4) + (g_FrameCount & 0xF)) * 5) >> 5);
            RotTransPers(g_ScratchPadVectors, (long*)&tile->x0, (long*)&p, (long*)&flag);

            Area_CellAddPrim(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, 1, sizeof(TILE_1));
        }
    }

    mode = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_SET_DRAW_MODE(mode);
    Area_CellAddPrim(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, 1, sizeof(DR_MODE));
}

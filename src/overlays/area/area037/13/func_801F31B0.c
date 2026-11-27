#include "area037_13.h"

#include <inline_c.h>

/* Draws the eight glowing spokes of the ring at its fixed cell, 32 dots each, while the camera is within ten cells of it. */
MATCH void func_801F31B0(void) {
    TILE_1* tile;
    s32     i;
    s32     j;
    s32     value;

    if ((g_AreaDrawFlags & AREA_DRAW_CELL_LAYERS) && abs(g_AreaCamera.scroll_x.part.integer - 0x2D) < 0xB && abs(g_AreaCamera.scroll_y.part.integer - 0x23) < 0xB) {
        D_1F800034[0] = -0x2980;
        D_1F800034[1] = -0x2E80;
        for (j = 0; j < 8; j++) {
            if ((j & 3) == 0) {
                SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 320, 256), 0);
                Area_CellAddPrim(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, (j >> 3) == 0, sizeof(DR_MODE));
            }
            for (i = 0; i < 32; i++) {
                tile = (TILE_1*)g_GfxPrimCursor;
                SetTile1(tile);
                SetSemiTrans(tile, 1);
                value = (0x17F - ((i << 3) + (g_FrameCount & 0x7))) >> 1;
                setRGB0(tile, value / 4, value / 4, value);
                g_ScratchPadVectors[0].vx = D_1F800034[0] + ((u32)(rsin(j * 0x200 - 0x100) * ((i << 4) + (g_FrameCount & 0xF)) * 5) >> 16);
                g_ScratchPadVectors[0].vy = D_1F800034[1] + ((u32)(rcos(j * 0x200 - 0x100) * ((i << 4) + (g_FrameCount & 0xF)) * 5) >> 16);
                g_ScratchPadVectors[0].vz = -0x140 - (rsin(((i << 4) + (g_FrameCount & 0xF)) * 5) >> 5);
                gte_ldv0(g_ScratchPadVectors);
                gte_rtps();
                gte_stsxy2(&tile->x0);
                Area_CellAddPrim(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, (j >> 3) == 0, sizeof(TILE_1));
            }
        }
    }
}

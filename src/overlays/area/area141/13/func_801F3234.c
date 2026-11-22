#include "area141_13.h"

MATCH void func_801F3234(void) {
    TILE_1* tile;
    long    depth;
    long    flag;
    s32     shade;
    s32     i;
    s32     j;

    if (TASK(Actor)->header.step == 0) {
        TASK(Actor)->pos.z.fixed = Area_HeightSample(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed);
        TASK(Actor)->header.step++;
    }

    if (abs(g_AreaTargetCellX - COORD_INT(TASK(Actor)->pos.x)) + abs(g_AreaTargetCellY - COORD_INT(TASK(Actor)->pos.y)) >= 0x15) {
        return;
    }

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 320, 256), 0);
    Area_CellAddPrim(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed, 1, sizeof(DR_MODE));

    TASK(Actor)->timer += 2;

    for (i = 0; i < 16; i++) {
        shade = ~(TASK(Actor)->timer - i * 16) & 0xFF;
        for (j = 0; j < 16; j++) {
            tile = (TILE_1*)g_GfxPrimCursor;
            SetTile1(tile);
            SetSemiTrans(tile, 1);
            setRGB0(tile, shade, shade, shade);
            g_ScratchPadVectors[0].vx = (TASK(Actor)->pos.x.fixed >> 9) - 0x4000 + (rsin((j << 8) + (u8)(g_FrameCount << 4) * D_801F47F4[i & 1]) >> 6) * 3;
            g_ScratchPadVectors[0].vy = (TASK(Actor)->pos.y.fixed >> 9) - 0x4000 + (rcos((j << 8) + (u8)(g_FrameCount << 4) * D_801F47F4[i & 1]) >> 6) * 3;
            g_ScratchPadVectors[0].vz = -TASK(Actor)->pos.z.fixed / 2 - (u8)(TASK(Actor)->timer - i * 16) * 2;
            RotTransPers(&g_ScratchPadVectors[0], (long*)&tile->x0, &depth, &flag);
            Area_CellAddPrim(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed, 1, sizeof(TILE_1));
        }
    }

    GFX_SET_DRAW_MODE(getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 320, 256));
    Area_CellAddPrim(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed, 1, sizeof(DR_MODE));
}

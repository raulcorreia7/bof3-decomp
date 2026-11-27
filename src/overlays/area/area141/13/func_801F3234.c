#include "area141_13.h"

MATCH void func_801F3234(void) {
    TILE_1* tile;
    long    depth;
    long    flag;
    s32     shade;
    s32     i;
    s32     j;

    if (SELF(Actor)->header.step == 0) {
        SELF(Actor)->pos.z.fixed = Area_HeightSample(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed);
        SELF(Actor)->header.step++;
    }

    if (abs(g_AreaCamera.scroll_x.part.integer - COORD_INT(SELF(Actor)->pos.x)) + abs(g_AreaCamera.scroll_y.part.integer - COORD_INT(SELF(Actor)->pos.y)) >= 0x15) {
        return;
    }

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 320, 256), 0);
    Area_CellAddPrim(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, 1, sizeof(DR_MODE));

    SELF(Actor)->timer += 2;

    for (i = 0; i < 16; i++) {
        shade = ~(SELF(Actor)->timer - i * 16) & 0xFF;
        for (j = 0; j < 16; j++) {
            tile = (TILE_1*)g_GfxPrimCursor;
            SetTile1(tile);
            SetSemiTrans(tile, 1);
            setRGB0(tile, shade, shade, shade);
            g_ScratchPadVectors[0].vx = (SELF(Actor)->pos.x.fixed >> 9) - 0x4000 + (rsin((j << 8) + (u8)(g_FrameCount << 4) * D_801F47F4[i & 1]) >> 6) * 3;
            g_ScratchPadVectors[0].vy = (SELF(Actor)->pos.y.fixed >> 9) - 0x4000 + (rcos((j << 8) + (u8)(g_FrameCount << 4) * D_801F47F4[i & 1]) >> 6) * 3;
            g_ScratchPadVectors[0].vz = -SELF(Actor)->pos.z.fixed / 2 - (u8)(SELF(Actor)->timer - i * 16) * 2;
            RotTransPers(&g_ScratchPadVectors[0], (long*)&tile->x0, &depth, &flag);
            Area_CellAddPrim(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, 1, sizeof(TILE_1));
        }
    }

    GFX_SET_DRAW_MODE(getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 320, 256));
    Area_CellAddPrim(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, 1, sizeof(DR_MODE));
}

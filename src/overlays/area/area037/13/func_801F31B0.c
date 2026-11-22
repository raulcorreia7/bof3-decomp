#include "area037_13.h"

#include <inline_c.h>

#ifdef NON_MATCHING
NON_MATCHING void func_801F31B0(void) {
    TILE_1* tile;
    s32     i;
    s32     j;
    s32     value;
    s32     angle;
    s32     phase;

    if ((g_AreaDrawFlags & AREA_DRAW_CELL_LAYERS) && abs(g_AreaTargetCellX - 0x2D) < 0xB && abs(g_AreaTargetCellY - 0x23) < 0xB) {
        D_1F800034[0] = -0x2980;
        D_1F800034[1] = -0x2E80;
        for (j = 0; j < 8; j++) {
            angle = j * 0x200 - 0x100;
            if ((j & 3) == 0) {
                SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, (GetGraphType() == 1 || GetGraphType() == 2) ? 0x2A5 : 0xB5, 0);
                Area_CellAddPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, (j >> 3) == 0, sizeof(DR_MODE));
            }
            for (i = 0; i < 32; i++) {
                tile = (TILE_1*)g_GfxPrimCursor;
                SetTile1(tile);
                PSX_SET_SEMI_TRANSPARENT(tile);
                value = (0x17F - ((i << 3) + (g_FrameCount & 0x7))) >> 1;
                setRGB0(tile, value / 4, value / 4, value);
                phase                     = (i << 4) + (g_FrameCount & 0xF);
                g_ScratchPadVectors[0].vx = D_1F800034[0] + ((u32)(rsin(angle) * phase * 5) >> 16);
                g_ScratchPadVectors[0].vy = D_1F800034[1] + ((u32)(rcos(angle) * phase * 5) >> 16);
                g_ScratchPadVectors[0].vz = -0x140 - (rsin(phase * 5) >> 5);
                gte_ldv0(g_ScratchPadVectors);
                gte_rtps();
                gte_stsxy2(&tile->x0);
                Area_CellAddPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, (j >> 3) == 0, sizeof(TILE_1));
            }
        }
    }
}
#else
INCLUDE_ASM(func_801F31B0);
#endif

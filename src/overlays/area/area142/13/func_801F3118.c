#include "area142_13.h"

/* The scroll target's tile ring: a 16 by 16 grid of semi-transparent, shaded tiles. */
MATCH void func_801F3118(void) {
    TILE_1* tile;
    s32     fade;
    s32     i;
    s32     j;
    long    depth;
    long    flag;

    if (abs(g_AreaTargetCellX - COORD_INT(SELF(Actor)->pos.x)) + abs(g_AreaTargetCellY - COORD_INT(SELF(Actor)->pos.y)) >= 0x15) {
        return;
    }

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, (GetGraphType() == 1 || GetGraphType() == 2) ? 0x2A5 : 0xB5, 0);
    Area_CellAddPrim(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, 1, sizeof(DR_MODE));

    SELF(Actor)->timer += 2;

    for (i = 0; i < 16; i++) {
        fade = ~(SELF(Actor)->timer - (i << 4)) & 0xFF;
        for (j = 0; j < 16; j++) {
            tile = (TILE_1*)g_GfxPrimCursor;
            SetTile1(tile);
            SetSemiTrans(tile, 1);
            setRGB0(tile, fade, fade, fade);

            g_ScratchPadVectors[0].vx = (SELF(Actor)->pos.x.fixed >> 9) + (s16)((rsin((j << 8) + (u8)(g_FrameCount << 4) * D_801F355C[i & 1]) >> 6) * 3 - 0x4000);
            g_ScratchPadVectors[0].vy = (SELF(Actor)->pos.y.fixed >> 9) + (s16)((rcos((j << 8) + (u8)(g_FrameCount << 4) * D_801F355C[i & 1]) >> 6) * 3 - 0x4000);
            g_ScratchPadVectors[0].vz = -0x180 - ((u8)(SELF(Actor)->timer - (i << 4)) << 1);
            RotTransPers(g_ScratchPadVectors, (long*)&tile->x0, &depth, &flag);

            Area_CellAddPrim(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, 1, sizeof(TILE_1));
        }
    }

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, (GetGraphType() == 1 || GetGraphType() == 2) ? 0x2A5 : 0xB5, 0);
    Area_CellAddPrim(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, 1, sizeof(DR_MODE));
}

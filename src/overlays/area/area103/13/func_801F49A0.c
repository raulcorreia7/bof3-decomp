#include "area103_13.h"

#ifdef NON_MATCHING
/* Draws the sixteen-cell light pillar around the actor: the corner heights come from the ground
 * sample and the cell's four depth scales. */
NON_MATCHING void func_801F49A0(s32 phase) {
    POLY_FT4*        prim;
    s16              x;
    s16              y;
    s16              height;
    s32              i;
    s32              cell_x;
    s32              cell_y;
    s32              part;
    u8               tile;
    LightPillarQuad* quad;
    long             depth;
    long             flag;

    if ((g_AreaDrawFlags & AREA_DRAW_CELL_LAYERS) == 0) {
        return;
    }
    D_1F800034_U16[0] = (TASK(Actor)->pos.x.fixed >> 9) - 0x4000;
    D_1F800034_U16[1] = (TASK(Actor)->pos.y.fixed >> 9) - 0x4000;
    for (i = 0; i < 16; i++) {
        GFX_SET_DRAW_MODE(getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256));
        cell_y = i >> 2;
        cell_x = i & 3;
        Area_CellAddPrim(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed, (s8)(cell_y + cell_x - 1), 0xC);

        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);

        x                         = D_1F800034_U16[0] + cell_x * 128 - 0x40;
        y                         = D_1F800034_U16[1] + cell_y * 128 - 0x40;
        g_ScratchPadVectors[0].vx = x;
        g_ScratchPadVectors[0].vy = y;
        height                    = Area_HeightSample((x + 0x4000) << 9, (y + 0x4000) << 9);
        g_ScratchPadVectors[0].vz = (-height / 2) - (D_801F5994[i].shade[0] * TASK(Actor)->unk_32) / 128;

        x                         = D_1F800034_U16[0] + cell_x * 128 + 0x40;
        y                         = D_1F800034_U16[1] + cell_y * 128 - 0x40;
        g_ScratchPadVectors[1].vx = x;
        g_ScratchPadVectors[1].vy = y;
        height                    = Area_HeightSample((x + 0x4000) << 9, (y + 0x4000) << 9);
        g_ScratchPadVectors[1].vz = (-height / 2) - (D_801F5994[i].shade[1] * TASK(Actor)->unk_32) / 128;

        x                         = D_1F800034_U16[0] + cell_x * 128 - 0x40;
        y                         = D_1F800034_U16[1] + cell_y * 128 + 0x40;
        g_ScratchPadVectors[2].vx = x;
        g_ScratchPadVectors[2].vy = y;
        height                    = Area_HeightSample((x + 0x4000) << 9, (y + 0x4000) << 9);
        g_ScratchPadVectors[2].vz = (-height / 2) - (D_801F5994[i].shade[2] * TASK(Actor)->unk_32) / 128;

        x                         = D_1F800034_U16[0] + cell_x * 128 + 0x40;
        y                         = D_1F800034_U16[1] + cell_y * 128 + 0x40;
        g_ScratchPadVectors[3].vx = x;
        g_ScratchPadVectors[3].vy = y;
        height                    = Area_HeightSample((x + 0x4000) << 9, (y + 0x4000) << 9);
        g_ScratchPadVectors[3].vz = (-height / 2) - (D_801F5994[i].shade[3] * TASK(Actor)->unk_32) / 128;

        if (D_801F5994[i].page != 0) {
            RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x1, (long*)&prim->x0, (long*)&prim->x3, (long*)&prim->x2,
                          &depth, &flag);
        } else {
            RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                          &depth, &flag);
        }
        quad = &D_801F5994[i];
        tile = quad->tile[phase];
        part = D_801F5994[i].page | 0x2580;
        if (phase == 0) {
            part = D_801F5994[i].page | 0x2180;
        }
        Area_ApplyTileToQuad((part << 16) | tile, prim, 1);
        Area_CellAddPrim(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed, (s8)((i >> 2) + (i & 3) - 1), 0x28);
    }
}
#else
INCLUDE_ASM(func_801F49A0);
#endif

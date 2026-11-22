#include "area091_13.h"

#ifdef NON_MATCHING
/* Draws the three spiral rings of fading lines and tiles around the task, then clears the
 * scene mode once the last ring has faded out. */
NON_MATCHING void func_801F35F4(void) {
    LINE_F2* line;
    TILE_1*  tile;
    long     depth;
    long     flag;
    s32      ring;
    s32      i;
    s32      radius;
    s32      shade;
    s32      half;
    s32      angle;

    if (g_AreaSceneMode == 0) {
        return;
    }
    g_ScratchPadVectors[0].vx = (TASK(Actor)->pos.x.fixed >> 9) - 0x4000;
    D_1F800016                = (TASK(Actor)->pos.y.fixed >> 9) - 0x4000;
    D_1F800018                = 0x80;
    RotTransPers(g_ScratchPadVectors, (long*)D_1F800034, &depth, &flag);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 320, 256), NULL);
    Area_CellAddPrim(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed, 2, sizeof(DR_MODE));
    TASK(Actor)->timer += 4;
    for (ring = 0; ring < 3; ring++) {
        radius = TASK(Actor)->timer - (ring << 5);
        if (radius < 0) {
            radius = 0;
        }
        shade = 0xC8 - (TASK(Actor)->timer - (ring << 4));
        if (shade >= 0x100) {
            shade = 0xFF;
        }
        if (shade < 0) {
            shade = 0;
        }
        half = shade / 2;
        for (i = 0; i < 0x40; i++) {
            line = (LINE_F2*)g_GfxPrimCursor;
            SetLineF2(line);
            SetSemiTrans(line, 1);
            line->r0 = half;
            line->g0 = half;
            line->b0 = shade;
            line->x0 = D_1F800034[0] + ((rsin(i << 6) * radius) >> 14);
            line->y0 = D_1F800034[1] + ((rcos(i << 6) * radius) >> 15);
            line->x1 = D_1F800034[0] + ((rsin((i + 1) << 6) * radius) >> 14);
            line->y1 = D_1F800034[1] + ((rcos((i + 1) << 6) * radius) >> 15);
            Area_CellAddPrim(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed, 2, sizeof(LINE_F2));
        }
        half = radius / 2;
        for (i = 0; i < 0x10; i++) {
            angle = (i << 8) + ((g_FrameCount << 4) & 0xFF) * D_801F3BA4[ring];
            tile  = (TILE_1*)g_GfxPrimCursor;
            SetTile1(tile);
            SetSemiTrans(tile, 1);
            tile->r0 = shade;
            tile->g0 = shade;
            tile->b0 = shade;
            tile->x0 = D_1F800034[0] + ((rsin(angle) * radius) >> 13);
            tile->y0 = D_1F800034[1] + ((rcos(angle) * radius) >> 14) - half;
            Area_CellAddPrim(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed, 2, sizeof(TILE_1));
        }
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 320, 256), NULL);
    Area_CellAddPrim(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed, 2, sizeof(DR_MODE));
    if (shade == 0) {
        g_AreaSceneMode = 0;
    }
}
#else
INCLUDE_ASM(func_801F35F4);
#endif

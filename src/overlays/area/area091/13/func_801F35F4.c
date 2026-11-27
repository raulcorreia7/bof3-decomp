#include "area091_13.h"

/* Three rings of fading lines and tiles around the task; the scene mode clears once the last has faded. */
MATCH void func_801F35F4(void) {
    LINE_F2* line;
    TILE_1*  tile;
    long     depth;
    long     flag;
    s32      ring;
    s32      i;
    s32      radius;
    s32      shade;
    s32      timer;

    if (g_AreaSceneMode == 0) {
        return;
    }
    g_ScratchPadVectors[0].vx = (SELF(Actor)->pos.x.fixed >> 9) - 0x4000;
    D_1F800016                = (SELF(Actor)->pos.y.fixed >> 9) - 0x4000;
    D_1F800018                = 0x80;
    RotTransPers(g_ScratchPadVectors, (long*)D_1F800034, &depth, &flag);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 320, 256), NULL);
    Area_CellAddPrim(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, 2, sizeof(DR_MODE));
    SELF(Actor)->timer += 4;
    for (ring = 0; ring < 3; ring++) {
        timer  = SELF(Actor)->timer;
        radius = timer - (ring << 5);
        radius = radius < 0 ? 0 : radius;
        shade  = 0xC8 - (timer - (ring << 4));
        shade  = shade > 0xFF ? 0xFF : shade;
        shade  = shade < 0 ? 0 : shade;
        for (i = 0; i < 0x40; i++) {
            line = (LINE_F2*)g_GfxPrimCursor;
            SetLineF2(line);
            SetSemiTrans(line, 1);
            line->r0 = shade / 2;
            line->g0 = shade / 2;
            line->b0 = shade;
            line->x0 = D_1F800034[0] + ((rsin(i << 6) * radius) >> 14);
            line->y0 = D_1F800034[1] + ((rcos(i << 6) * radius) >> 15);
            line->x1 = D_1F800034[0] + ((rsin((i + 1) << 6) * radius) >> 14);
            line->y1 = D_1F800034[1] + ((rcos((i + 1) << 6) * radius) >> 15);
            Area_CellAddPrim(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, 2, sizeof(LINE_F2));
        }
        for (i = 0; i < 0x10; i++) {
            tile = (TILE_1*)g_GfxPrimCursor;
            SetTile1(tile);
            SetSemiTrans(tile, 1);
            tile->r0 = shade;
            tile->g0 = shade;
            tile->b0 = shade;
            tile->x0 = D_1F800034[0] + ((rsin((i << 8) + ((g_FrameCount << 4) & 0xFF) * D_801F3BA4[ring]) * radius) >> 13);
            tile->y0 = D_1F800034[1] + ((rcos((i << 8) + ((g_FrameCount << 4) & 0xFF) * D_801F3BA4[ring]) * radius) >> 14) - radius / 2;
            Area_CellAddPrim(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, 2, sizeof(TILE_1));
        }
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 320, 256), NULL);
    Area_CellAddPrim(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, 2, sizeof(DR_MODE));
    if (shade == 0) {
        g_AreaSceneMode = 0;
    }
}

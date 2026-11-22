#include "area106_13.h"

#ifdef NON_MATCHING
/* Draws one waterfall layer ring: a cap pair, sixteen half-shade segments, a second cap pair and
 * thirty-two further segments, once per of the three layers. */
NON_MATCHING void func_801F33D4(s32 size) {
    LINE_F2* prim;
    s32      layer;
    s32      radius;
    s32      shade;
    s32      i;
    s32      angle;
    s32      value;
    long     depth;
    long     flag;

    GFX_ADD_DITHERED_DRAW_MODE(GFX_LAYER_SCENE_BACK, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 320, 256));
    g_ScratchPadVectors[0].vz = -0x3F8;
    for (layer = 0; layer < 3; layer++) {
        radius = size - layer * 16;
        if (radius < 0) {
            radius = 0;
        }
        shade = 0xC8 - (size * 5 - layer * 16);
        if (shade >= 0x100) {
            shade = 0xFF;
        }
        if (shade < 0) {
            shade = 0;
        }
        prim = (LINE_F2*)g_GfxPrimCursor;
        SetLineF2(prim);
        SetSemiTrans(prim, 1);
        value                     = shade / 2;
        prim->r0                  = value;
        prim->g0                  = value;
        prim->b0                  = shade;
        g_ScratchPadVectors[0].vx = -0x37C0;
        g_ScratchPadVectors[0].vy = (radius << 2) - 0x2CC0;
        RotTransPers(&g_ScratchPadVectors[0], (long*)&prim->x0, &depth, &flag);
        g_ScratchPadVectors[0].vx = -0x3640;
        RotTransPers(&g_ScratchPadVectors[0], (long*)&prim->x1, &depth, &flag);
        GFX_AddPrim(GFX_LAYER_SCENE_BACK, sizeof(LINE_F2));
        D_1F800034[0] = -0x3640;
        D_1F800034[1] = -0x2CC0;
        for (i = 0; i < 16; i++) {
            prim = (LINE_F2*)g_GfxPrimCursor;
            SetLineF2(prim);
            SetSemiTrans(prim, 1);
            angle                     = i * 64;
            prim->r0                  = value;
            prim->g0                  = value;
            prim->b0                  = value;
            g_ScratchPadVectors[0].vx = D_1F800034[0] + ((rsin(angle) * radius) >> 10);
            g_ScratchPadVectors[0].vy = D_1F800034[1] + ((rcos(angle) * radius) >> 10);
            RotTransPers(&g_ScratchPadVectors[0], (long*)&prim->x0, &depth, &flag);
            angle                     = (i + 1) * 64;
            g_ScratchPadVectors[0].vx = D_1F800034[0] + ((rsin(angle) * radius) >> 10);
            g_ScratchPadVectors[0].vy = D_1F800034[1] + ((rcos(angle) * radius) >> 10);
            RotTransPers(&g_ScratchPadVectors[0], (long*)&prim->x1, &depth, &flag);
            GFX_AddPrim(GFX_LAYER_SCENE_BACK, sizeof(LINE_F2));
        }

        prim = (LINE_F2*)g_GfxPrimCursor;
        SetLineF2(prim);
        SetSemiTrans(prim, 1);
        value                     = shade / 2;
        prim->r0                  = value;
        prim->g0                  = value;
        prim->b0                  = shade;
        g_ScratchPadVectors[0].vx = (radius << 2) - 0x3640;
        g_ScratchPadVectors[0].vy = -0x2DC0;
        RotTransPers(&g_ScratchPadVectors[0], (long*)&prim->x0, &depth, &flag);
        g_ScratchPadVectors[0].vy = -0x2CC0;
        RotTransPers(&g_ScratchPadVectors[0], (long*)&prim->x1, &depth, &flag);
        GFX_AddPrim(GFX_LAYER_SCENE_BACK, sizeof(LINE_F2));
        shade         = value;
        D_1F800034[0] = -0x3640;
        D_1F800034[1] = -0x2DC0;
        for (i = 0x10; i < 0x20; i++) {
            prim = (LINE_F2*)g_GfxPrimCursor;
            SetLineF2(prim);
            SetSemiTrans(prim, 1);
            angle                     = i * 64;
            prim->r0                  = shade;
            prim->g0                  = shade;
            prim->b0                  = shade;
            g_ScratchPadVectors[0].vx = D_1F800034[0] + ((rsin(angle) * radius) >> 10);
            g_ScratchPadVectors[0].vy = D_1F800034[1] + ((rcos(angle) * radius) >> 10);
            RotTransPers(&g_ScratchPadVectors[0], (long*)&prim->x0, &depth, &flag);
            angle                     = (i + 1) * 64;
            g_ScratchPadVectors[0].vx = D_1F800034[0] + ((rsin(angle) * radius) >> 10);
            g_ScratchPadVectors[0].vy = D_1F800034[1] + ((rcos(angle) * radius) >> 10);
            RotTransPers(&g_ScratchPadVectors[0], (long*)&prim->x1, &depth, &flag);
            GFX_AddPrim(GFX_LAYER_SCENE_BACK, sizeof(LINE_F2));
        }
    }
    GFX_ADD_LAYER_DRAW_MODE(GFX_LAYER_SCENE_BACK, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 320, 256));
}
#else
INCLUDE_ASM(func_801F33D4);
#endif

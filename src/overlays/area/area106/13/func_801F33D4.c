#include "area106_13.h"

/* Draws one waterfall layer ring: a cap pair, sixteen half-shade segments, a second cap pair and
 * thirty-two further segments, once for each of the three layers. */
MATCH void func_801F33D4(s32 size) {
    LINE_F2* prim;
    s32      layer;
    s32      shade;
    s32      radius;
    s32      i;
    s32      rim;
    s32      fade;
    long     depth;
    long     flag;

    GFX_ADD_DITHERED_DRAW_MODE(GFX_LAYER_SCENE_BACK, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 320, 256));
    g_ScratchPadVectors[0].vz = -0x3F8;
    for (layer = 0; layer < 3; layer++) {
        radius = size - layer * 16;
        radius = (radius < 0) ? 0 : radius;
        shade  = 0xC8 - (size * 5 - layer * 16);
        shade  = (shade >= 0x100) ? 0xFF : shade;
        shade  = (shade < 0) ? 0 : shade;
        prim   = (LINE_F2*)g_GfxPrimCursor;
        SetLineF2(prim);
        SetSemiTrans(prim, 1);
        setRGB0(prim, shade / 2, shade / 2, shade);
        g_ScratchPadVectors[0].vx = -0x37C0;
        g_ScratchPadVectors[0].vy = ((radius << 12) >> 10) - 0x2CC0;
        RotTransPers(&g_ScratchPadVectors[0], (long*)&prim->x0, &depth, &flag);
        g_ScratchPadVectors[0].vx = -0x3640;
        D_1F800016         = ((radius << 12) >> 10) - 0x2CC0;
        RotTransPers(&g_ScratchPadVectors[0], (long*)&prim->x1, &depth, &flag);
        GFX_AddPrim(GFX_LAYER_SCENE_BACK, sizeof(LINE_F2));
        rim               = shade / 2;
        D_1F800034_S16 = -0x3640;
        D_1F800036_S16 = -0x2CC0;
        for (i = 0; i < 16; i++) {
            prim = (LINE_F2*)g_GfxPrimCursor;
            SetLineF2(prim);
            SetSemiTrans(prim, 1);
            setRGB0(prim, rim, rim, rim);
            g_ScratchPadVectors[0].vx = (u16)D_1F800034_S16 + ((rsin(i * 64) * radius) >> 10);
            g_ScratchPadVectors[0].vy = (u16)D_1F800036_S16 + ((rcos(i * 64) * radius) >> 10);
            RotTransPers(&g_ScratchPadVectors[0], (long*)&prim->x0, &depth, &flag);
            g_ScratchPadVectors[0].vx = (u16)D_1F800034_S16 + ((rsin((i + 1) * 64) * radius) >> 10);
            D_1F800016         = (u16)D_1F800036_S16 + ((rcos((i + 1) * 64) * radius) >> 10);
            RotTransPers(&g_ScratchPadVectors[0], (long*)&prim->x1, &depth, &flag);
            GFX_AddPrim(GFX_LAYER_SCENE_BACK, sizeof(LINE_F2));
        }

        prim = (LINE_F2*)g_GfxPrimCursor;
        SetLineF2(prim);
        SetSemiTrans(prim, 1);
        setRGB0(prim, shade / 2, shade / 2, shade);
        g_ScratchPadVectors[0].vx = ((radius << 12) >> 10) - 0x3640;
        D_1F800016         = -0x2DC0;
        RotTransPers(&g_ScratchPadVectors[0], (long*)&prim->x0, &depth, &flag);
        g_ScratchPadVectors[0].vx = ((radius << 12) >> 10) - 0x3640;
        D_1F800016         = -0x2CC0;
        RotTransPers(&g_ScratchPadVectors[0], (long*)&prim->x1, &depth, &flag);
        GFX_AddPrim(GFX_LAYER_SCENE_BACK, sizeof(LINE_F2));
        fade              = shade / 2;
        D_1F800034_S16 = -0x3640;
        D_1F800036_S16 = -0x2DC0;
        for (i = 16; i < 32; i++) {
            prim = (LINE_F2*)g_GfxPrimCursor;
            SetLineF2(prim);
            SetSemiTrans(prim, 1);
            setRGB0(prim, fade, fade, fade);
            g_ScratchPadVectors[0].vx = (u16)D_1F800034_S16 + ((rsin(i * 64) * radius) >> 10);
            g_ScratchPadVectors[0].vy = (u16)D_1F800036_S16 + ((rcos(i * 64) * radius) >> 10);
            RotTransPers(&g_ScratchPadVectors[0], (long*)&prim->x0, &depth, &flag);
            g_ScratchPadVectors[0].vx = (u16)D_1F800034_S16 + ((rsin((i + 1) * 64) * radius) >> 10);
            D_1F800016         = (u16)D_1F800036_S16 + ((rcos((i + 1) * 64) * radius) >> 10);
            RotTransPers(&g_ScratchPadVectors[0], (long*)&prim->x1, &depth, &flag);
            GFX_AddPrim(GFX_LAYER_SCENE_BACK, sizeof(LINE_F2));
        }
    }
    GFX_ADD_LAYER_DRAW_MODE(GFX_LAYER_SCENE_BACK, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 320, 256));
}

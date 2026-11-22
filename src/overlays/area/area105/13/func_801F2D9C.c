#include "area105_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F2D9C(s32 phase) {
    RECT*     window;
    POLY_FT4* prim;
    SVECTOR*  quad;
    long      depth;
    long      flag;
    u8*       uv;
    s32       offset;
    s32       depth_z;
    s32       left;
    s32       right;
    s32       top;
    s32       bottom;
    s32       i;

    window          = (RECT*)g_GfxPrimCursor;
    g_GfxPrimCursor = (u8*)(window + 1);
    window->x       = 0x60;
    window->y       = 0x10;
    window->w       = 0x10;
    window->h       = 0x10;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 704, 256), window);
    GFX_AddPrim(GFX_LAYER_SCENE_BACK, sizeof(DR_MODE));

    uv      = D_801F3320 + 0x10;
    offset  = phase * 4;
    depth_z = (phase * 6) - 0x380;
    quad    = g_ScratchPadVectors;
    for (i = 0; i < 3; i++) {
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        SetSemiTrans(prim, 1);
        prim->tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_QUARTER, 704, 256);
        prim->clut  = 0x78C6;
        left        = ((uv[i * 4] - 0x80) << 7) + offset - 0x40;
        right       = ((uv[i * 4] + uv[i * 4 + 2] - 0x81) << 7) + offset + 0x40;
        top         = ((uv[i * 4 + 1] - 0x80) << 7) + offset - 0x40;
        bottom      = ((uv[i * 4 + 1] + uv[i * 4 + 3] - 0x81) << 7) + offset + 0x40;
        quad[0].vx  = left;
        quad[0].vy  = top;
        quad[0].vz  = depth_z;
        quad[1].vx  = right;
        quad[1].vy  = top;
        quad[1].vz  = depth_z;
        quad[2].vx  = left;
        quad[2].vy  = bottom;
        quad[2].vz  = depth_z;
        quad[3].vx  = right;
        quad[3].vy  = bottom;
        quad[3].vz  = depth_z;
        if (i == 2) {
            quad[0].vx = left + (phase << 3);
            quad[0].vy = top + (phase << 3);
        }
        prim->u0 = 0;
        prim->v0 = 0;
        prim->u1 = (uv[i * 4 + 2] << 4) - 1;
        prim->v1 = 0;
        prim->u2 = 0;
        prim->v2 = (uv[i * 4 + 3] << 4) - 1;
        prim->u3 = (uv[i * 4 + 2] << 4) - 1;
        prim->v3 = (uv[i * 4 + 3] << 4) - 1;
        prim->r0 = 0x80;
        prim->g0 = 0x80;
        prim->b0 = 0x80;
        RotTransPers4(&quad[0], &quad[1], &quad[2], &quad[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
        GFX_AddPrim(GFX_LAYER_SCENE_BACK, sizeof(POLY_FT4));
    }

    window          = (RECT*)g_GfxPrimCursor;
    g_GfxPrimCursor = (u8*)(window + 1);
    window->x       = 0;
    window->y       = 0;
    window->w       = 0x100;
    window->h       = 0x100;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 704, 256), window);
    GFX_AddPrim(GFX_LAYER_SCENE_BACK, sizeof(DR_MODE));
}
#else
INCLUDE_ASM(func_801F2D9C);
#endif

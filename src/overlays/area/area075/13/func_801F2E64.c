#include "area075_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F2E64(s32 phase, s32 semi_trans) {
    POLY_FT4* prim;
    RECT      window;
    s32       origin;
    s32       shade;

    prim     = (POLY_FT4*)g_GfxPrimCursor;
    window.x = 0xD0;
    window.y = 0x40;
    setWH(&window, 0x10, 0x10);
    g_GfxPrimCursor = (u8*)prim + 8;
    SetTexWindow((DR_TWIN*)((u8*)prim + 8), &window);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 1, 0xC);

    origin = (u16)phase << 15;
    Area_HeightSample(g_Task->pos.x.fixed - origin, g_Task->pos.y.fixed);

    SetPolyFT4(prim);
    Camera_ProjectPoint((s32*)g_Task, (DVECTOR*)&prim->x0);
    Camera_ProjectPoint((s32*)g_Task, (DVECTOR*)((u8*)prim + 0x10));
    Camera_ProjectPoint((s32*)g_Task, (DVECTOR*)((u8*)prim + 0x18));

    prim->clut  = GetClut(0xD0, 0x1E3);
    prim->tpage = GetTPage(0, 1, 0, 0x2C0);
    shade       = g_Task->tint.bytes.flags & 7;
    prim->r0    = shade + 0x80;
    prim->g0    = shade + 0x80;
    prim->b0    = shade + 0x80;
    shade       = g_Task->tint.bytes.rgb.r & 7;
    prim->u0    = shade;
    prim->v0    = shade;
    prim->r0    = g_Task->tint.bytes.rgb.b;
    prim->g0    = g_Task->tint.bytes.rgb.b;
    prim->b0    = g_Task->tint.bytes.rgb.b;
    SetSemiTrans(prim, semi_trans & 0xFF);
    SetShadeTex(prim, 0);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 1, sizeof(POLY_FT4));

    prim            = (POLY_FT4*)g_GfxPrimCursor;
    g_GfxPrimCursor = (u8*)prim + 8;
    window.x        = 0;
    window.y        = 0;
    setWH(&window, 0x100, 0x100);
    SetTexWindow((DR_TWIN*)((u8*)prim + 8), &window);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 1, 0xC);
}
#else
INCLUDE_ASM(func_801F2E64);
#endif

#include "area075_13.h"

/* The target cell's projected quad and the texture window it is cut from. */
MATCH void func_801F2E64(s32 phase, s32 semi_trans) {
    POLY_FT4* prim;
    s16*      rect;
    s16*      next;
    s32       corner[3];
    s32       origin;
    s32       height;

    rect            = (s16*)g_GfxPrimCursor;
    rect[0]         = 0xD0;
    rect[1]         = 0x40;
    next            = rect + 4;
    g_GfxPrimCursor = (u8*)next;
    rect[2]         = 0x10;
    rect[3]         = 0x10;
    SetTexWindow((DR_TWIN*)next, (RECT*)rect);
    Area_CellAddPrim(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, 1, 0xC);

    origin = (u16)phase << 15;
    height = Area_HeightSample(SELF(Actor)->pos.x.fixed - origin, SELF(Actor)->pos.y.fixed) << 16;

    prim = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);

    corner[0] = SELF(Actor)->pos.x.fixed - origin;
    corner[1] = SELF(Actor)->pos.y.fixed - 0x8000;
    corner[2] = height + 0xE00000;
    Camera_ProjectPoint(corner, (DVECTOR*)&prim->x0);

    corner[0] = SELF(Actor)->pos.x.fixed;
    corner[1] = SELF(Actor)->pos.y.fixed - 0x8000;
    corner[2] = SELF(Actor)->pos.z.fixed + 0xE00000;
    Camera_ProjectPoint(corner, (DVECTOR*)&prim->x1);

    corner[0] = SELF(Actor)->pos.x.fixed - origin;
    corner[1] = SELF(Actor)->pos.y.fixed + 0x8000;
    corner[2] = height + 0xE00000;
    Camera_ProjectPoint(corner, (DVECTOR*)&prim->x2);

    corner[0] = SELF(Actor)->pos.x.fixed;
    corner[1] = SELF(Actor)->pos.y.fixed + 0x8000;
    corner[2] = SELF(Actor)->pos.z.fixed + 0xE00000;
    Camera_ProjectPoint(corner, (DVECTOR*)&prim->x3);

    setClut(prim, 0xD0, 0x1E3);
    prim->tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 704, 256);

    setUVWH(prim, SELF(Actor)->unk_0A & 0x7, 0, 0x80, 0x10);
    setRGB0(prim, SELF(Actor)->tint.bytes.rgb.r, SELF(Actor)->tint.bytes.rgb.r, SELF(Actor)->tint.bytes.rgb.r);
    SetSemiTrans(prim, semi_trans & 0xFF);
    SetShadeTex(prim, 0);
    Area_CellAddPrim(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, 1, sizeof(POLY_FT4));

    rect            = (s16*)g_GfxPrimCursor;
    next            = rect + 4;
    g_GfxPrimCursor = (u8*)next;
    rect[0]         = 0;
    rect[1]         = 0;
    rect[2]         = 0x100;
    rect[3]         = 0x100;
    SetTexWindow((DR_TWIN*)next, (RECT*)rect);
    Area_CellAddPrim(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, 1, 0xC);
}

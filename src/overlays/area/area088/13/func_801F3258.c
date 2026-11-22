#include "area088_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3258(u8* window) {
    TrailPoint* point;
    POLY_G4*    prim;
    POLY_G4*    copy;
    s32         colour;
    s32         shade;
    u16         i;
    TrailPoint* next;

    GFX_ADD_DITHERED_DRAW_MODE(1, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 0x3C0, 0) & 0xFFFF);
    point = (TrailPoint*)window;
    GFX_DrawFan(&point->screen, point->width, (u16)point->angle - 0x400, 0x80);
    colour = 0x80;
    shade  = 0x7C;
    for (i = 0, next = point + 1; i < TRAIL_LENGTH - 1; i++, point++, next++) {
        if (*(u32*)&point->screen == *(u32*)&next->screen) {
            continue;
        }
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        setXY4(prim, point[0].screen.vx, point[0].screen.vy, point[0].screen.vx + ((u16)point[0].width * rcos(((u16)point[0].angle) + 0x400) >> 12),
               point[0].screen.vy + ((u16)point[0].width * rsin((u16)point[0].angle + 0x400) >> 12), next[0].screen.vx, next[0].screen.vy,
               next[0].screen.vx + ((u16)next[0].width * rcos((u16)next[0].angle + 0x400) >> 12), next[0].screen.vy + ((u16)next[0].width * rsin((u16)next[0].angle + 0x400) >> 12));
        setRGB0(prim, colour, colour, colour);
        setRGB1(prim, 0, 0, 0);
        setRGB2(prim, shade, shade, shade);
        setRGB3(prim, 0, 0, 0);
        GFX_AddPrim(1, sizeof(POLY_G4));
        copy     = (POLY_G4*)g_GfxPrimCursor;
        *copy    = *prim;
        copy->x1 = point[0].screen.vx + ((u16)point[0].width * rcos((u16)point[0].angle - 0x400) >> 12);
        copy->y1 = point[0].screen.vy + ((u16)point[0].width * rsin((u16)point[0].angle - 0x400) >> 12);
        copy->x3 = next[0].screen.vx + ((u16)next[0].width * rcos((u16)next[0].angle - 0x400) >> 12);
        copy->y3 = next[0].screen.vy + ((u16)next[0].width * rsin((u16)next[0].angle - 0x400) >> 12);
        colour -= 4;
        shade -= 4;
        GFX_AddPrim(1, sizeof(POLY_G4));
    }
    GFX_DrawFan(&point->screen, point->width, (u16)point->angle + 0x400, colour & 0xFF);
}
#else
INCLUDE_ASM(func_801F3258);
#endif

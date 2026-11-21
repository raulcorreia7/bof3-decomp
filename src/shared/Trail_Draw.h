#include "area/effects.h"

/* Trail_Draw (Trail_Draw in scena07, Trail_Draw in scena08): draws the trail as a ribbon, a fan at
 * each end and two shaded POLY_G4 quads between each pair of points that differ on screen. */
MATCH void Trail_Draw(Trail* trail) {
    TrailPoint* point;
    POLY_G4*    prim;
    s32         colour;
    s32         shade;
    u16         i;
    TrailPoint* next;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 0x3C0, 0) & 0xFFFF, NULL);
    GFX_AddPrim(1, sizeof(DR_MODE));
    GFX_DrawFan(&trail->point[0].screen, trail->point[0].width, (u16)(trail->point[0].angle - 0x400), 0x80);
    colour = 0x80;
    shade  = 0x7C;
    point  = trail->point;
    for (i = 0, next = point + 1; i < TRAIL_LENGTH - 1; point++, next++, i++) {
        if (*(u32*)&point->screen == *(u32*)&next->screen) {
            continue;
        }
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        prim->x0 = point[0].screen.vx;
        prim->y0 = point[0].screen.vy;
        prim->x1 = point[0].screen.vx + ((u16)point[0].width * rcos((u16)point[0].angle + 0x400) >> 12);
        prim->y1 = point[0].screen.vy + ((u16)point[0].width * rsin((u16)point[0].angle + 0x400) >> 12);
        prim->x2 = next[0].screen.vx;
        prim->y2 = next[0].screen.vy;
        prim->x3 = next[0].screen.vx + ((u16)next[0].width * rcos((u16)next[0].angle + 0x400) >> 12);
        prim->y3 = next[0].screen.vy + ((u16)next[0].width * rsin((u16)next[0].angle + 0x400) >> 12);
        prim->b0 = colour;
        prim->g0 = colour;
        prim->r0 = colour;
        prim->r1 = prim->g1 = prim->b1 = 0;
        prim->b2 = shade;
        prim->g2 = shade;
        prim->r2 = shade;
        prim->r3 = prim->g3 = prim->b3 = 0;
        GFX_AddPrim(1, sizeof(POLY_G4));
        prim     = (POLY_G4*)g_GfxPrimCursor;
        *prim    = prim[-1];
        prim->x1 = point[0].screen.vx + ((u16)point[0].width * rcos((u16)point[0].angle - 0x400) >> 12);
        prim->y1 = point[0].screen.vy + ((u16)point[0].width * rsin((u16)point[0].angle - 0x400) >> 12);
        prim->x3 = next[0].screen.vx + ((u16)next[0].width * rcos((u16)next[0].angle - 0x400) >> 12);
        prim->y3 = next[0].screen.vy + ((u16)next[0].width * rsin((u16)next[0].angle - 0x400) >> 12);
        colour -= 4;
        shade -= 4;
        GFX_AddPrim(1, sizeof(POLY_G4));
    }
    GFX_DrawFan(&point->screen, point->width, (u16)(point->angle + 0x400), colour & 0xFF);
}

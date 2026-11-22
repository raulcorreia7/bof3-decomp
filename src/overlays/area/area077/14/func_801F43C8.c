#include "area077_14.h"

/* Draws the trail ribbon: one fading quad per pair of neighbouring slot edges. */
MATCH void func_801F43C8(void) {
    DVECTOR   first;
    DVECTOR   second;
    MATRIX    matrix;
    POLY_G4*  prim;
    AreaSlot* slot;
    s32       tpage;
    u8        i;
    u8        shade;

    tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 960, 0);
    GFX_ADD_DITHERED_DRAW_MODE(GFX_LAYER_UI, tpage & HALF_MASK);
    Camera_SetMatrix(&matrix);
    Camera_ProjectPoint(&MEM_PTR(AreaSlot, AREA_WORK)->edges[0].vx, &first);
    Camera_ProjectPoint(&MEM_PTR(AreaSlot, AREA_WORK)->edges[1].vx, &second);

    slot  = MEM_PTR(AreaSlot, AREA_WORK);
    shade = 0x40;
    i     = 0;
    do {
        prim = (POLY_G4*)g_GfxPrimCursor;
        slot++;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        i++;
        setXY2(prim, first.vx, first.vy, second.vx, second.vy);
        prim->r0 = prim->r1 = shade;
        prim->g0 = prim->b0 = prim->g1 = prim->b1 = shade / 2;
        Camera_ProjectPoint(&slot->edges[0].vx, &first);
        Camera_ProjectPoint(&slot->edges[1].vx, &second);
        shade--;
        prim->x2 = first.vx;
        prim->y2 = first.vy;
        prim->x3 = second.vx;
        prim->y3 = second.vy;
        prim->r2 = prim->r3 = shade;
        prim->g2 = prim->b2 = prim->g3 = prim->b3 = shade / 2;
        GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_G4));
    } while (i < AREA_SLOT_COUNT - 1);
}

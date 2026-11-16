#include "area077_14.h"

/* Draws the trail ribbon: one fading quad per pair of neighbouring slot edges. */
#ifdef NON_MATCHING
NON_MATCHING void func_801F43C8(void) {
    DVECTOR   first;
    DVECTOR   second;
    MATRIX    matrix;
    POLY_G4*  prim;
    AreaSlot* slot;
    s32       tpage;
    u8        i;
    u8        shade;

    tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 960, 0);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage & HALF_MASK, 0);
    GFX_AddPrim(1, sizeof(DR_MODE));
    Area_SetCameraMatrix(&matrix);
    Area_ProjectPoint((s32*)&MEM_PTR(AreaSlot, AREA_WORK)->edges[0], &first);
    Area_ProjectPoint((s32*)&MEM_PTR(AreaSlot, AREA_WORK)->edges[1], &second);

    slot  = MEM_PTR(AreaSlot, AREA_WORK);
    shade = 0x40;
    i     = 0;
    do {
        prim = (POLY_G4*)g_GfxPrimCursor;
        slot++;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        i++;
        prim->x0 = first.vx;
        prim->y0 = first.vy;
        prim->x1 = second.vx;
        prim->y1 = second.vy;
        setRGB0(prim, shade, shade / 2, shade / 2);
        setRGB1(prim, shade, shade / 2, shade / 2);
        Area_ProjectPoint((s32*)&slot->edges[0], &first);
        Area_ProjectPoint((s32*)&slot->edges[1], &second);
        shade--;
        prim->x2 = first.vx;
        prim->y2 = first.vy;
        prim->x3 = second.vx;
        prim->y3 = second.vy;
        setRGB2(prim, shade, shade / 2, shade / 2);
        setRGB3(prim, shade, shade / 2, shade / 2);
        GFX_AddPrim(1, sizeof(POLY_G4));
    } while (i < AREA_SLOT_COUNT - 1);
}
#else
INCLUDE_ASM(func_801F43C8);
#endif

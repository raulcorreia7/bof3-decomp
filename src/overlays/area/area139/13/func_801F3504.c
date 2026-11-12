#include "area139_13.h"

#include "overlays/area/Area_DrawWedgeDiscBody.h"

MATCH void func_801F3504(s32 x, s32 y, s16 radius, u16 angle) {
    AREA_DRAW_WEDGE_DISC_BODY(D_801F442C, D_801F442D, D_801F442E, Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 1, sizeof(POLY_G3)));
}

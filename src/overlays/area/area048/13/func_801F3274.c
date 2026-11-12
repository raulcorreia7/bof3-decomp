#include "area048_13.h"

#include "overlays/area/Area_DrawWedgeDiscBody.h"

MATCH void func_801F3274(s32 x, s32 y, s16 radius, u16 angle) {
    AREA_DRAW_WEDGE_DISC_BODY(D_801F4D5C, D_801F4D5D, D_801F4D5E, GFX_AddPrim(3, sizeof(POLY_G3)));
}

#include "area042_13.h"

#include "overlays/area/Area_DrawWedgeDiscBody.h"

MATCH void func_801F30C0(s32 x, s32 y, s16 radius, u16 angle) {
    AREA_DRAW_WEDGE_DISC_BODY(D_801F52C4, D_801F52C5, D_801F52C6, GFX_AddPrim(3, sizeof(POLY_G3)));
}

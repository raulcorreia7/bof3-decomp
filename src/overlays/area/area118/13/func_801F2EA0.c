#include "area118_13.h"

#include "overlays/area/Area_DrawDimQuad.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F2EA0(void) {
    POLY_G4* prim;

    if (g_Task->timer++ >= 16) {
        D_801F59EC    = D_801F511C[D_801F59E8];
        g_Task->timer = 0;
        if (D_801F59E8++ >= 7) {
            D_801F59E8 = 0;
        }
    }
    AREA_DRAW_DIM_QUAD(2, D_801F59EC);
}
#else
INCLUDE_ASM(func_801F2EA0);
#endif

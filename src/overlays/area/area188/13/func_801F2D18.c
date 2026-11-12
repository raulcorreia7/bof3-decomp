#include "area188_13.h"

#include "overlays/area/Area_DrawDimQuad.h"

MATCH void func_801F2D18(void) {
    AREA_DRAW_DIM_QUAD(2);

    if (g_ScriptVars[0] == 1) {
        func_80196070();
    }
}

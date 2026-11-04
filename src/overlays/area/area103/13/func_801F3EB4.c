#include "area103_13.h"

MATCH void func_801F3EB4(void) {
    if (g_SpadWork->y.part.integer < 0x1C) {
        g_SpadWork->x.fixed -= 0x800;
        g_SpadWork->y.fixed += 0x800;
    } else {
        g_SpadWork->state_02++;
    }
    Area_StepSceneFrame();
}

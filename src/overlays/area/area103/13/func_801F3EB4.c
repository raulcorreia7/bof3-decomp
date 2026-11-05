#include "area103_13.h"

MATCH void func_801F3EB4(void) {
    if (COORD_INT(g_Task->y) < 0x1C) {
        g_Task->x.fixed -= 0x800;
        g_Task->y.fixed += 0x800;
    } else {
        g_Task->step++;
    }
    Area_StepSceneFrame();
}

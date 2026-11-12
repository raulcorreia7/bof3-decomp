#include "area103_13.h"

MATCH void func_801F3EB4(void) {
    if (COORD_INT(g_Task->pos.y) < 28) {
        g_Task->pos.x.fixed -= 0x800;
        g_Task->pos.y.fixed += 0x800;
    } else {
        g_Task->header.step++;
    }
    Area_StepSceneFrame();
}

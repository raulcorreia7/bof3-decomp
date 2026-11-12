#include "area103_13.h"

MATCH void func_801F3E10(void) {
    if (COORD_INT(g_Task->pos.y) < 25) {
        g_Task->pos.y.fixed += 0x1000;
    } else {
        g_Task->header.step++;
    }
    Area_StepSceneFrame();
}

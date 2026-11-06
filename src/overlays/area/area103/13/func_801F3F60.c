#include "area103_13.h"

MATCH void func_801F3F60(void) {
    if (COORD_INT(g_Task->x) >= 0x4F) {
        g_Task->x.fixed -= 0x1000;
    } else if (((g_FrameCount / 5) & 3) == 3) {
        g_Task->header.step++;
    }
    Area_StepSceneFrame();
}

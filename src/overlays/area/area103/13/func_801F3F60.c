#include "area103_13.h"

MATCH void func_801F3F60(void) {
    if (g_Task->x.part.integer >= 0x4F) {
        g_Task->x.fixed -= 0x1000;
    } else if (((g_FrameCount / 5) & 3) == 3) {
        g_Task->step++;
    }
    Area_StepSceneFrame();
}

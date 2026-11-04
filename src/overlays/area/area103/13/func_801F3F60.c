#include "area103_13.h"

MATCH void func_801F3F60(void) {
    if (g_SpadWork->x.part.integer >= 0x4F) {
        g_SpadWork->x.fixed -= 0x1000;
    } else if (((g_FrameCount / 5) & 3) == 3) {
        g_SpadWork->state_02++;
    }
    Area_StepSceneFrame();
}

#include "area103_13.h"

MATCH void func_801F3E10(void) {
    if (g_SpadWork->y.part.integer < 0x19) {
        g_SpadWork->y.fixed += 0x1000;
    } else {
        g_SpadWork->state_02++;
    }
    Area_StepSceneFrame();
}

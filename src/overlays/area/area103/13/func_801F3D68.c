#include "area103_13.h"

MATCH void func_801F3D68(void) {
    s16 timer;

    timer = g_Task->unk_32;
    if (timer < 0x80) {
        g_Task->unk_32 = timer + 1;
    } else {
        g_Task->header.step++;
        *g_ScriptVars = 0xD;
    }
    Area_StepSceneFrame();
}

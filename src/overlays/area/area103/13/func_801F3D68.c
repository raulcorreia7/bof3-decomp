#include "area103_13.h"

MATCH void func_801F3D68(void) {
    s16 timer;

    timer = TASK(Actor)->unk_32;
    if (timer < 128) {
        TASK(Actor)->unk_32 = timer + 1;
    } else {
        TASK(Actor)->header.step++;
        *g_ScriptVars = 0xD;
    }
    Area_StepSceneFrame();
}

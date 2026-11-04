#include "area103_13.h"

MATCH void func_801F3D68(void) {
    s16 timer;

    timer = g_SpadWork->unk_32;
    if (timer < 0x80) {
        g_SpadWork->unk_32 = timer + 1;
    } else {
        g_SpadWork->state_02++;
        *g_ScriptVars = 0xD;
    }
    Area_StepSceneFrame();
}

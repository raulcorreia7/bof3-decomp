#include "area082_13.h"

MATCH void func_801F4D6C(void) {
    if (g_ScriptVars[0] == 0x32) {
        SND_PlayCue(0x208);
        g_Task->unk_09 = 0;
        g_Task->header.step++;
    }
}

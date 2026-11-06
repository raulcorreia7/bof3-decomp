#include "area120_13.h"

MATCH void func_801F2D40(void) {
    func_801F36B0();
    if (g_ScriptVars[0] == 0x11) {
        SND_PlayCue(0x203);
        SND_PlayCue(0x202);
        g_Task->unk_06 = 2;
        g_Task->header.mode++;
    }
}

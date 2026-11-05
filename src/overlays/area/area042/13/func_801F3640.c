#include "area042_13.h"

MATCH void func_801F3640(void) {
    Actor* actor;

    if (SYS_TestFlag(g_SceneEventFlags, 0x11)) {
        SND_PlayCue(0x202);
        actor          = g_Task;
        actor->unk_0B  = 0x80;
        actor->z.fixed = -0x180;
        g_Task->unk_09 = 0;
        g_Task->step += 1;
        func_801F37A8(-0x180, 0x800000);
    }
}

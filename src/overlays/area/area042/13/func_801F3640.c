#include "area042_13.h"

MATCH void func_801F3640(void) {
    Actor* actor;

    if (SYS_TestFlag(g_SceneEventFlags, 0x11)) {
        SND_PlayCue(0x202);
        actor              = g_SpadWork;
        actor->unk_0B      = 0x80;
        actor->z.fixed     = -0x180;
        g_SpadWork->unk_09 = 0;
        g_SpadWork->state_02 += 1;
        func_801F37A8(-0x180, 0x800000);
    }
}

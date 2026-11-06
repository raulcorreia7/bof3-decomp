#include "area042_13.h"

MATCH void func_801F3640(void) {
    Actor* actor;

    if (SYS_TestFlag(g_SaveData.scene_event_flags, 0x11)) {
        SND_PlayCue(0x202);
        actor              = g_Task;
        actor->unk_0B      = 0x80;
        actor->pos.z.fixed = -0x180;
        g_Task->unk_09     = 0;
        g_Task->header.step += 1;
        func_801F37A8(-0x180, 0x800000);
    }
}

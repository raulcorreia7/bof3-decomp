#include "area042_13.h"

MATCH void func_801F3640(void) {
    Actor* actor;

    if (SYS_TestFlag(g_SceneEventFlags, 17)) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x02));
        actor               = g_Task;
        actor->param.unk_0B = 0x80;
        actor->pos.z.fixed  = -0x180;
        g_Task->timer       = 0;
        g_Task->header.step += 1;
        func_801F37A8(-0x180, 0x800000);
    }
}

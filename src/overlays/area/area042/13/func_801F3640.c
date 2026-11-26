#include "area042_13.h"

MATCH void func_801F3640(void) {
    Actor* actor;

    if (SYS_TestFlag(g_SceneEventFlags, 17)) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x02));
        actor               = SELF(Actor);
        actor->param.unk_0B = 0x80;
        actor->pos.z.fixed  = -0x180;
        SELF(Actor)->timer  = 0;
        SELF(Actor)->header.step += 1;
        func_801F37A8(-0x180, 0x800000);
    }
}

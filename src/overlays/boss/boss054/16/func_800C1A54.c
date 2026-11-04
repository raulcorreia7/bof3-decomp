#include "boss054_16.h"

MATCH void func_800C1A54(void) {
    PartyBattler* saved;

    saved      = g_SpadWork;
    g_SpadWork = D_801EC2E0->work_74.party;
    Actor_SelectScript(2);
    g_SpadWork    = saved;
    saved->unk_0C = 8;
    saved->step_01++;
}

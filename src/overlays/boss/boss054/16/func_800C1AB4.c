#include "boss054_16.h"

MATCH void func_800C1AB4(void) {
    PartyBattler* saved_work;
    s32           timer;

    timer                               = ((PartyBattler*)g_SpadWork)->unk_0C - 1;
    ((PartyBattler*)g_SpadWork)->unk_0C = timer;
    if (timer == 0) {
        SND_PlayCue(0x601U);
        ((PartyBattler*)g_SpadWork)->step_01 += 1;
    }
    saved_work                  = ((PartyBattler*)g_SpadWork);
    ((PartyBattler*)g_SpadWork) = D_801EC2E0->target.party;
    func_8014DAEC();
    ((PartyBattler*)g_SpadWork) = saved_work;
}

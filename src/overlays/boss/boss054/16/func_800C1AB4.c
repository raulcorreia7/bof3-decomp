#include "boss054_16.h"

MATCH void func_800C1AB4(void) {
    PartyBattler *temp_s0;
    s32 temp_v0;

    temp_v0 = ((PartyBattler *)g_SpadWork)->unk_0C - 1;
    ((PartyBattler *)g_SpadWork)->unk_0C = temp_v0;
    if (temp_v0 == 0) {
        SND_PlayCue(0x601U);
        ((PartyBattler *)g_SpadWork)->step_01 += 1;
    }
    temp_s0 = ((PartyBattler *)g_SpadWork);
    ((PartyBattler *)g_SpadWork) = D_801EC2E0->target.party;
    func_8014DAEC();
    ((PartyBattler *)g_SpadWork) = temp_s0;
}

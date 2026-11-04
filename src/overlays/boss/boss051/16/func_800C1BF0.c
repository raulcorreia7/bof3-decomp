#include "boss051_16.h"

MATCH void func_800C1BF0(void) {
    PartyBattler* temp_s0;
    s32           temp_v1;
    u8            temp_a0;
    u8            temp_v0;

    temp_s0                     = ((PartyBattler*)g_SpadWork);
    ((PartyBattler*)g_SpadWork) = D_801EB4E0;
    func_8014DAEC();
    ((PartyBattler*)g_SpadWork) = temp_s0;
    temp_a0                     = temp_s0->unk_09;
    temp_v1                     = temp_a0 & 0xFF;
    if (temp_v1 != 0xFF) {
        if (temp_v1 == 0) {
            SND_PlayCue(0x601U);
            ((PartyBattler*)g_SpadWork)->unk_09 = 0xFF;
        } else {
            temp_s0->unk_09 = temp_a0 - 1;
        }
    }
    temp_v0 = ((PartyBattler*)g_SpadWork)->unk_0A;
    if (temp_v0 == 0) {
        D_801EB4E0->step_01 = 5;
        D_801EB4E0->unk_02  = 0;
        func_800A9820(g_BattleTargetSelector);
        ((PartyBattler*)g_SpadWork)->step_01 += 1;
        return;
    }
    ((PartyBattler*)g_SpadWork)->unk_0A = temp_v0 - 1;
}

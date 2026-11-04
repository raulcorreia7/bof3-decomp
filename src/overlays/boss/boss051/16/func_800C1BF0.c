#include "boss051_16.h"

MATCH void func_800C1BF0(void) {
    PartyBattler* battler;
    s32           value;
    u8            value2;
    u8            value3;

    battler                     = ((PartyBattler*)g_SpadWork);
    ((PartyBattler*)g_SpadWork) = D_801EB4E0;
    func_8014DAEC();
    ((PartyBattler*)g_SpadWork) = battler;
    value2                      = battler->unk_09;
    value                       = value2 & 0xFF;
    if (value != 0xFF) {
        if (value == 0) {
            SND_PlayCue(0x601U);
            ((PartyBattler*)g_SpadWork)->unk_09 = 0xFF;
        } else {
            battler->unk_09 = value2 - 1;
        }
    }
    value3 = ((PartyBattler*)g_SpadWork)->unk_0A;
    if (value3 == 0) {
        D_801EB4E0->step_01 = 5;
        D_801EB4E0->unk_02  = 0;
        func_800A9820(g_BattleTargetSelector);
        ((PartyBattler*)g_SpadWork)->step_01 += 1;
        return;
    }
    ((PartyBattler*)g_SpadWork)->unk_0A = value3 - 1;
}

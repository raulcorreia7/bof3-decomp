#include "boss054_16.h"

MATCH void func_800C1AB4(void) {
    PartyBattler* saved_work;
    s32           timer;

    timer                           = ((PartyBattler*)g_Task)->unk_0C - 1;
    ((PartyBattler*)g_Task)->unk_0C = timer;
    if (timer == 0) {
        SND_PlayCue(0x601U);
        ((PartyBattler*)g_Task)->header.mode += 1;
    }
    saved_work              = ((PartyBattler*)g_Task);
    ((PartyBattler*)g_Task) = D_801EC2E0->target.party;
    func_8014DAEC();
    ((PartyBattler*)g_Task) = saved_work;
}

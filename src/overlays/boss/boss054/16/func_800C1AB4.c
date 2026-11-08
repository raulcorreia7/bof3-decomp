#include "boss054_16.h"

MATCH void func_800C1AB4(void) {
    PartyMember* saved_work;
    s32          timer;

    timer                          = ((PartyMember*)g_Task)->unk_0C - 1;
    ((PartyMember*)g_Task)->unk_0C = timer;
    if (timer == 0) {
        SND_PlayCue(EMI_CUE_ID(6, 1));
        ((PartyMember*)g_Task)->header.mode += 1;
    }
    saved_work             = ((PartyMember*)g_Task);
    ((PartyMember*)g_Task) = D_801EC2E0->target.party;
    func_8014DAEC();
    ((PartyMember*)g_Task) = saved_work;
}

#include "boss054_16.h"

MATCH void func_800C1AB4(void) {
    PartyMember* saved_work;
    s32          timer;

    timer                          = ((PartyMember*)g_Task)->unk_0C - 1;
    ((PartyMember*)g_Task)->unk_0C = timer;
    if (timer == 0) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_ENEMY, 1));
        ((PartyMember*)g_Task)->header.mode += 1;
    }
    saved_work             = ((PartyMember*)g_Task);
    ((PartyMember*)g_Task) = D_801EC2E0->target.party;
    Script_AnimStepOnce();
    ((PartyMember*)g_Task) = saved_work;
}

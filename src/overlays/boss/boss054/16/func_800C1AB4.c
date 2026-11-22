#include "boss054_16.h"

MATCH void func_800C1AB4(void) {
    PartyMember* saved_work;
    s32          timer;

    timer                     = TASK(PartyMember)->unk_0C - 1;
    TASK(PartyMember)->unk_0C = timer;
    if (timer == 0) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_ENEMY, 1));
        TASK(PartyMember)->header.mode += 1;
    }
    saved_work          = (TASK(PartyMember));
    (TASK(PartyMember)) = D_801EC2E0->target.party;
    Script_AnimStepOnce();
    (TASK(PartyMember)) = saved_work;
}

#include "boss054_16.h"

MATCH void func_800C1AB4(void) {
    PartyMember* saved_work;
    s32          timer;

    timer                     = SELF(PartyMember)->unk_0C - 1;
    SELF(PartyMember)->unk_0C = timer;
    if (timer == 0) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_ENEMY, 1));
        SELF(PartyMember)->header.mode += 1;
    }
    saved_work          = (SELF(PartyMember));
    (SELF(PartyMember)) = D_801EC2E0->target.party;
    Script_AnimStepOnce();
    (SELF(PartyMember)) = saved_work;
}

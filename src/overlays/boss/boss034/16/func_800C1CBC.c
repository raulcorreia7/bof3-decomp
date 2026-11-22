#include "boss034_16.h"

MATCH void func_800C1CBC(void) {
    Script_AnimStepLoop();
    if (EMI_IsReady() != 0) {
        Battle_DefeatEnemy();
        TASK(PartyMember)->header.flags &= ~PARTY_MEMBER_FLAG_HANDLER_BUSY;
        TASK(PartyMember)->header.mode = 6;
        TASK(PartyMember)->header.step = 4;
        TASK(PartyMember)->unk_03      = 6;
    }
}

#include "boss034_16.h"

MATCH void func_800C1CBC(void) {
    Script_AnimStepLoop();
    if (EMI_IsReady() != 0) {
        Battle_DefeatEnemy();
        SELF(PartyMember)->header.flags &= ~PARTY_MEMBER_FLAG_HANDLER_BUSY;
        SELF(PartyMember)->header.mode = 6;
        SELF(PartyMember)->header.step = 4;
        SELF(PartyMember)->unk_03      = 6;
    }
}

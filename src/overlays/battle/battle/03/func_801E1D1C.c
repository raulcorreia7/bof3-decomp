#include "battle_03.h"

MATCH void func_801E1D1C(void) {
    if (EMI_IsReady() != 0) {
        Script_Request(SELF(PartyMember)->facing + 0x24u);
        Battle_IsPartyMemberBlocked();
        SELF(PartyMember)->header.step += 1;
    }
}

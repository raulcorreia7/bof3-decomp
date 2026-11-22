#include "battle_03.h"

MATCH void func_801E1D1C(void) {
    if (EMI_IsReady() != 0) {
        Script_Request(TASK(PartyMember)->facing + 0x24u);
        Battle_IsPartyMemberBlocked();
        TASK(PartyMember)->header.step += 1;
    }
}

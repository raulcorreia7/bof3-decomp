#include "battle_03.h"

MATCH void func_801E1938(void) {
    if (Battle_IsPartyMemberBlocked() != 0u) {
        TASK(PartyMember)->header.mode = (TASK(PartyMember)->header.mode + 1u);
        TASK(PartyMember)->header.step = 0u;
    }
}

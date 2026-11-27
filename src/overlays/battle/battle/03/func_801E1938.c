#include "battle_03.h"

MATCH void func_801E1938(void) {
    if (Battle_IsPartyMemberBlocked() != 0u) {
        SELF(PartyMember)->header.mode = (SELF(PartyMember)->header.mode + 1u);
        SELF(PartyMember)->header.step = 0u;
    }
}

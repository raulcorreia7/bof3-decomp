#include "battle_03.h"

MATCH void func_801E1D88(void) {
    if ((Battle_IsPartyMemberBlocked() & BYTE_MASK) != 0u) {
        SELF(PartyMember)->header.mode = 8u;
        SELF(PartyMember)->header.step = 0u;
    }
}

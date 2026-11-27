#include "battle_03.h"

MATCH void func_801E4D34(void) {
    if (Battle_IsEnemyBlockedOnce() != 0u) {
        SELF(PartyMember)->header.mode = (SELF(PartyMember)->header.mode + 1u);
        SELF(PartyMember)->header.step = 0u;
    }
}

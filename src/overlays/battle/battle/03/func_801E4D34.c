#include "battle_03.h"

MATCH void func_801E4D34(void) {
    if (Battle_IsEnemyBlockedOnce() != 0u) {
        TASK(PartyMember)->header.mode = (TASK(PartyMember)->header.mode + 1u);
        TASK(PartyMember)->header.step = 0u;
    }
}

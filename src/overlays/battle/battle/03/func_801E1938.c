#include "battle_03.h"

MATCH void func_801E1938(void) {
    if (Battle_IsPartyMemberBlocked() != 0u) {
        BATTLE_WORK->header.mode = (BATTLE_WORK->header.mode + 1u);
        BATTLE_WORK->header.step = 0u;
    }
}

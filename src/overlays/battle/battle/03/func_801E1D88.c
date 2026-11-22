#include "battle_03.h"

MATCH void func_801E1D88(void) {
    if ((Battle_IsPartyMemberBlocked() & BYTE_MASK) != 0u) {
        BATTLE_WORK->header.mode = 8u;
        BATTLE_WORK->header.step = 0u;
    }
}

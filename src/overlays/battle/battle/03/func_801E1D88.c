#include "battle_03.h"

MATCH void func_801E1D88(void) {
    if ((Battle_IsPartyMemberBlocked() & BYTE_MASK) != 0u) {
        g_Task->header.mode = 8u;
        g_Task->header.step = 0u;
    }
}

#include "battle_03.h"

MATCH void func_801E1938(void) {
    if (Battle_IsPartyMemberBlocked() != 0u) {
        g_Task->header.mode = (g_Task->header.mode + 1u);
        g_Task->header.step = 0u;
    }
}

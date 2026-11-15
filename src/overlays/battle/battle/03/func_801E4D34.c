#include "battle_03.h"

MATCH void func_801E4D34(void) {
    if (Battle_IsEnemyBlockedOnce() != 0u) {
        g_Task->header.mode = (g_Task->header.mode + 1u);
        g_Task->header.step = 0u;
    }
}

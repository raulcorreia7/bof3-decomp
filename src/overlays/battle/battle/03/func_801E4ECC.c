#include "battle_03.h"

MATCH void func_801E4ECC(void) {
    if ((D_801CA71C[g_Battle.action_id].mask & 0x800u) == 0u) {
        Battle_IsEnemyBlockedOnce();
    }
    g_Task->unk_09 += 1u;
}

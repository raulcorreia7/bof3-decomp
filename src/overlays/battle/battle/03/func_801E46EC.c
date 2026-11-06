#include "battle_03.h"

MATCH void func_801E46EC(void) {
    if (func_801E3160() != 0u) {
        g_Task->unk_03 += 1;
        if ((g_BattleCurrentEnemy->turn.damage_flags.value & 2u) != 0u) {
            func_801E2314(8);
        } else {
            func_801E2314(0);
        }
    }
}

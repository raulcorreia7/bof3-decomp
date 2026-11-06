#include "battle_03.h"

MATCH void func_801E2948(s8 enemy_index) {
    if (!(((rand() & 7) < 3) || (g_BattleLivingEnemyCount == 1u))) {
        (*(u8*)&g_BattleTargetSelector) = Battle_PickRandomTarget((enemy_index + 3));
    } else {
        (*(u8*)&g_BattleTargetSelector) = func_801E2E30();
    }
}

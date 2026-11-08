#include "battle_03.h"

MATCH u8* func_801DD760(u8 battler_index) {
    if (BATTLER_IS_PLAYER(battler_index)) {
        return (u8*)&g_Game.members[battler_index];
    }

    return g_BattleEnemies + ((battler_index * 36u - battler_index) * 8u);
}

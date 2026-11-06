#include "battle_03.h"

MATCH void Battle_SetTextEnemyName(u32 enemy_index) {
    SYS_CopyString(g_TextVariables[0], ENEMY_COMBATANT(enemy_index & BYTE_MASK).name, 8u);
}

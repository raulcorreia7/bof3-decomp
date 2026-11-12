#include "battle_15.h"

/* func_8009C868 */
MATCH u8 Battle_EnemyEventTriggered(volatile EnemyBattler* enemy, s32 bit_index) {
    return ((enemy->triggered_events >> bit_index) & 0x1U);
}

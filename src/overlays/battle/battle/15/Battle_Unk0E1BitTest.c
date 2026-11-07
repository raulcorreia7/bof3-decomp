#include "battle_15.h"

/* func_8009C868 */
MATCH u8 Battle_Unk0E1BitTest(volatile EnemyBattler* enemy, s32 bit_index) {
    return ((enemy->fired_events >> bit_index) & 1U);
}

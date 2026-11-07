#include "battle_15.h"

/* func_8009C87C */
MATCH void Battle_Unk0E1BitModify(EnemyBattler* enemy, s32 bit, u8 set) {
    u8 mask;

    mask = BIT(bit);
    if (set != 0) {
        enemy->fired_events |= mask;
    } else {
        enemy->fired_events &= ~mask;
    }
}

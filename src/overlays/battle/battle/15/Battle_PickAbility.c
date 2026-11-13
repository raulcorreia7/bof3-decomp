#include "battle_15.h"

s16 func_800A2D70(u8 battler_index, u16 element_mask);

/* func_800A3A10 */
MATCH u8 Battle_PickAbility(u8 battler_index, u8 selection_kind) {
    return BattleRollHitChance(selection_kind, func_800A2D70);
}

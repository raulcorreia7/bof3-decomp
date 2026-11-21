#include "battle_15.h"

s16 func_800A3060(u8 battler_index, u16 rule_mask);

MATCH u8 func_800A3C9C(u8 battler_index, u8 selection_type) {
    return BattleRollHitChance(selection_type, func_800A3060);
}

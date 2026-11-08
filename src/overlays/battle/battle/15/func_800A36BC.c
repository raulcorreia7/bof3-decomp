#include "battle_15.h"

MATCH u8 func_800A36BC(s32 battler_index, s32 compare_value) {
    return BattleCompareStatusByte(battler_index, compare_value, 0x84);
}

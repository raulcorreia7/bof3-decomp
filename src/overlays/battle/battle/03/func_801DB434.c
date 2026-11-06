#include "battle_03.h"

MATCH u32 func_801DB434(u8 compare_value, u32 row_index) {
    const volatile u8* base;
    const volatile u8* row;
    u8                 index;

    index = 0u;
    row_index &= 0xFF;
    base = g_BattleLevelThresholds;
    row  = base + row_index * BATTLE_LEVEL_THRESHOLD_COUNT;
    while (index < BATTLE_LEVEL_THRESHOLD_COUNT) {
        if (compare_value < row[index]) {
            return index;
        }
        index += 1u;
    }
    return BATTLE_LEVEL_THRESHOLD_COUNT;
}

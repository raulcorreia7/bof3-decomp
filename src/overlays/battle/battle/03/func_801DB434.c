#include "battle_03.h"

MATCH u32 func_801DB434(u8 compare_value, u32 side) {
    const volatile u8* base;
    const volatile u8* thresholds;
    u8                 index;

    index = 0u;
    side &= BYTE_MASK;
    base       = g_BattleLevelThresholds;
    thresholds = base + side * BATTLE_LEVEL_THRESHOLD_COUNT;
    while (index < BATTLE_LEVEL_THRESHOLD_COUNT) {
        if (compare_value < thresholds[index]) {
            return index;
        }
        index += 1u;
    }
    return BATTLE_LEVEL_THRESHOLD_COUNT;
}

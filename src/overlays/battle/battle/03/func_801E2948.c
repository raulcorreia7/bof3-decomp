#include "battle_03.h"

MATCH void func_801E2948(s8 enemy_index) {
    if (!((RANDOM_MASK(7) < 3) || (g_Battle.living_enemy_count == 1u))) {
        (*(u8*)&g_Battle.target_selector) = Battle_PickRandomTarget((enemy_index + 3));
    } else {
        (*(u8*)&g_Battle.target_selector) = Battle_PickFormationTarget();
    }
}

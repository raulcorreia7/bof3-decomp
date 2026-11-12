#include "battle_03.h"

MATCH u8 func_801E2D4C(u8 slot_offset) {
    u8 value;

    if (g_Battle.living_enemy_count == 1u) {
        value = Battle_PickFormationTarget();
    } else {
        value = Battle_PickRandomTarget((slot_offset + 3));
    }

    return value;
}

#include "battle_03.h"

MATCH u8 func_801E30B8(u8 slot_offset) {
    if (g_Battle.living_enemy_count != 1u) {
        return Battle_PickRandomTarget((slot_offset + 3));
    }

    return 0xFF;
}

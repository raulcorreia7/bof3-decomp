#include "battle_03.h"

MATCH u8 func_801E2D4C(u8 slot_offset) {
    u8 value;

    if (g_BattleLivingEnemyCount == 1u) {
        value = func_801E2E30();
    } else {
        value = Battle_PickRandomTarget((u8)(slot_offset + 3));
    }

    return value;
}

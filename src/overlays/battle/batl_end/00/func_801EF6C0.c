#include "batl_end_00.h"

MATCH s32 func_801EF6C0(void) {
    u8 slot;

    for (slot = 0; slot < g_Battle.party_count; slot++) {
        if (func_801DB524(slot) == 0) {
            if ((g_Game.members[slot].chr.equip.accessories[0] == ACCESSORY_MIDAS_STONE) ||
                (g_Game.members[slot].chr.equip.accessories[1] == ACCESSORY_MIDAS_STONE)) {
                return 1;
            }
        }
    }

    return 0;
}

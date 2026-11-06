#include "battle_03.h"

MATCH u8 func_801E7B34(void) {
    u8  index;
    u32 offset;

    for (index = 0u; index < BATTLE_PARTY_SLOT_COUNT; index++) {
        offset = index * BATTLE_PARTY_STRIDE;
        if ((s_BattleBattlerTemplates[offset] & 1u) == 0u) {
            return false;
        }
        if ((*(u32*)((s_BattleBattlerTemplateTails + offset)) & 1u) != 0u) {
            return true;
        }
    }
    return false;
}

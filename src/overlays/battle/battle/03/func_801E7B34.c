#include "battle_03.h"

MATCH u8 func_801E7B34(void) {
    u8 index;

    for (index = 0u; index < BATTLE_PARTY_CHARACTERS_COUNT; index++) {
        if ((s_BattleBattlerTemplates[index].header.flags & 0x1u) == 0u) {
            return false;
        }
        if ((s_BattleBattlerTemplates[index].u.turn.action_flags.value & COMBATANT_FLAG_DRAGON_FORM_QUEUED) != 0u) {
            return true;
        }
    }
    return false;
}

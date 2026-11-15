#include "battle_03.h"

/* resets one local/enemy `0x80` path, zeroes saved values, rebuilds
 * the followup state bytes, and queues the common event when needed.
 */
MATCH u8 func_801D5BC0(void) {
    u8 index;
    u8 count;

    count = 0u;
    for (index = 0u; index < BATTLE_PARTY_CHARACTERS_COUNT; index++) {
        if ((Battle_GetActionLock(index) == 0u) && (HAS_STATUS(g_Game.members[index], STATUS_POISONED))) {
            g_Game.members[index].u.turn.ap_change = 0u;
            g_Game.members[index].u.turn.hp_change = 0u;
            func_801DCEF8(index);
            count += 1u;
            g_Game.members[index].header.mode         = 6u;
            g_Game.members[index].header.step         = 5u;
            g_Game.members[index].unk_04              = 0u;
            g_Game.members[index].unk_03              = 0u;
            g_Game.members[index].u.turn.target_flags = 0x11u;
            Battle_SetSlotPending(index);
        }
    }

    for (index = 3u; index < 11u; index++) {
        if ((Battle_GetActionLock(index) == 0u) && ((ENEMY_COMBATANT(index).status & STATUS_POISONED) != 0u)) {
            ENEMY_COMBATANT(index).turn.ap_change = 0u;
            ENEMY_COMBATANT(index).turn.hp_change = 0u;
            func_801DCEF8(index);
            count += 1u;
            ENEMY_COMBATANT(index).header.mode       = 6u;
            ENEMY_COMBATANT(index).header.step       = 5u;
            ENEMY_COMBATANT(index).unk_04            = 0u;
            ENEMY_COMBATANT(index).unk_03            = 0u;
            ENEMY_COMBATANT(index).turn.target_flags = 0x11u;
            Battle_SetSlotPending(index);
        }
    }

    if (count != 0u) {
        Battle_OpenPanel();
        Battle_QueueEvent(2u, 0u, 0u, 45u, Message_GetText(0x18u));
        return true;
    }

    return false;
}

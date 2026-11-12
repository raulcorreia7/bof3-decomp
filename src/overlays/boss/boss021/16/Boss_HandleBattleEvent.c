#include "boss021_16.h"

MATCH u8 Boss_HandleBattleEvent(u32 mode) {
    u8 slot;

    switch ((u8)mode) {
        case BOSS_EVENT_TICK:
            for (slot = 0; slot < BATTLE_PARTY_CHARACTERS_COUNT; slot++) {
                if (Battle_SlotIsBlocked(slot & BYTE_MASK) == 0) {
                    g_Game.members[slot].chr.status |= STATUS_SILENCED;
                }
            }
            for (slot = 3; slot < COMBATANT_COUNT; slot++) {
                if (Battle_SlotIsBlocked(slot & BYTE_MASK) == 0) {
                    ENEMY_COMBATANT(slot & BYTE_MASK).status |= STATUS_SILENCED;
                }
            }
            break;
        case BOSS_EVENT_RESTART_BEGIN:
        case BOSS_EVENT_ACTION_START:
        case BOSS_EVENT_TURN_END:
        case BOSS_EVENT_EFFECTS_LOADED:
        case BOSS_EVENT_RESTART_END:
            break;
    }
    return 0;
}

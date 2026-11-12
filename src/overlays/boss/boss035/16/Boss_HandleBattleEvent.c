#include "boss035_16.h"

MATCH u8 Boss_HandleBattleEvent(u32 mode) {
    switch ((u8)mode) {
        case BOSS_EVENT_RESTART_BEGIN:
            if (Battle_SlotIsBlocked(3) != 0) {
                g_Battle.outcome.result |= BATTLE_RESULT_VICTORY;
            }
            break;
        case BOSS_EVENT_ACTION_START:
            break;
        case BOSS_EVENT_TURN_END:
            break;
        case BOSS_EVENT_TICK:
            break;
        case BOSS_EVENT_EFFECTS_LOADED:
            break;
        case BOSS_EVENT_RESTART_END:
            break;
    }
    return 0;
}

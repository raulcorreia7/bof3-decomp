#include "battle_15.h"

/* Applies the event packet and, for a once-only trigger, marks it triggered. */
#define BATTLE_TRIGGER_ENEMY_EVENT(condition)                 \
    if (condition) {                                          \
        Battle_ApplyEnemyEvent(g_BattleCurrentEnemy, packet); \
    }

#define BATTLE_TRIGGER_ENEMY_EVENT_ONCE(condition)                      \
    if (condition) {                                                    \
        if (Battle_EnemyEventTriggered(g_BattleCurrentEnemy, i) == 0) { \
            Battle_ApplyEnemyEvent(g_BattleCurrentEnemy, packet);       \
            Battle_SetEnemyEventTriggered(g_BattleCurrentEnemy, i, 1);  \
        }                                                               \
    }

/* walks the four battle event packets of the current enemy kind and
 * triggers the ones whose condition holds, then hands the frame to the
 * event dispatcher.
 */
/* func_8009BBE8 */
MATCH void Battle_TriggerEnemyEvents(void) {
    BattleEventPacket* packet;
    u8                 i;

    for (i = 0; i < ENEMY_AI_COUNT; i++) {
        packet = &BATTLE_ENEMY_EVENTS[g_BattleCurrentEnemy->kind].packets[i];
        switch (packet->kind) {
            case BATTLE_EVENT_HIT_FIRE:
                BATTLE_TRIGGER_ENEMY_EVENT_ONCE(Battle_ActionHasElement(ELEM_FIRE));
                break;
            case BATTLE_EVENT_HIT_FROST:
                BATTLE_TRIGGER_ENEMY_EVENT_ONCE(Battle_ActionHasElement(ELEM_FROST));
                break;
            case BATTLE_EVENT_HIT_ELECTRIC:
                BATTLE_TRIGGER_ENEMY_EVENT_ONCE(Battle_ActionHasElement(ELEM_ELECTRIC));
                break;
            case BATTLE_EVENT_HIT_EARTH:
                BATTLE_TRIGGER_ENEMY_EVENT_ONCE(Battle_ActionHasElement(ELEM_EARTH));
                break;
            case BATTLE_EVENT_HIT_WIND:
                BATTLE_TRIGGER_ENEMY_EVENT_ONCE(Battle_ActionHasElement(ELEM_WIND));
                break;
            case BATTLE_EVENT_HIT_HOLY:
                BATTLE_TRIGGER_ENEMY_EVENT_ONCE(Battle_ActionHasElement(ELEM_HOLY));
                break;
            case BATTLE_EVENT_HIT_PSIONIC:
                BATTLE_TRIGGER_ENEMY_EVENT_ONCE(Battle_ActionHasElement(ELEM_PSIONIC));
                break;
            case BATTLE_EVENT_HIT_DEATH:
                BATTLE_TRIGGER_ENEMY_EVENT_ONCE(Battle_ActionHasElement(ELEM_DEATH));
                break;
            case BATTLE_EVENT_HIT_STATUS:
                BATTLE_TRIGGER_ENEMY_EVENT_ONCE(Battle_ActionHasElement(ELEM_STATUS));
                break;
            case BATTLE_EVENT_HIT_BY_ABILITY:
                BATTLE_TRIGGER_ENEMY_EVENT_ONCE(LOBU(g_Battle.action_type) == BATTLE_ACTION_ABILITY && g_BattleCurrentEnemy->turn.hp_change != 0);
                break;
            case BATTLE_EVENT_HIT_BY_ATTACK:
                BATTLE_TRIGGER_ENEMY_EVENT_ONCE(LOBU(g_Battle.action_type) == BATTLE_ACTION_ATTACK && g_BattleCurrentEnemy->turn.hp_change != 0);
                break;
            case BATTLE_EVENT_BLINDED:
                BATTLE_TRIGGER_ENEMY_EVENT_ONCE((g_BattleCurrentEnemy->status & STATUS_BLIND) != 0);
                break;
            case BATTLE_EVENT_POISONED:
                BATTLE_TRIGGER_ENEMY_EVENT_ONCE((g_BattleCurrentEnemy->status & STATUS_POISONED) != 0);
                break;
            case BATTLE_EVENT_NO_DROP:
                BATTLE_TRIGGER_ENEMY_EVENT_ONCE(g_BattleCurrentEnemy->drops[0].rate == 0);
                break;
            case BATTLE_EVENT_REPEAT_HIT_FIRE:
                BATTLE_TRIGGER_ENEMY_EVENT(Battle_ActionHasElement(ELEM_FIRE));
                break;
            case BATTLE_EVENT_REPEAT_HIT_FROST:
                BATTLE_TRIGGER_ENEMY_EVENT(Battle_ActionHasElement(ELEM_FROST));
                break;
            case BATTLE_EVENT_REPEAT_HIT_ELECTRIC:
                BATTLE_TRIGGER_ENEMY_EVENT(Battle_ActionHasElement(ELEM_ELECTRIC));
                break;
            case BATTLE_EVENT_REPEAT_HIT_BY_ATTACK:
                BATTLE_TRIGGER_ENEMY_EVENT(LOBU(g_Battle.action_type) == BATTLE_ACTION_ATTACK && g_BattleCurrentEnemy->turn.hp_change != 0);
                break;
            case BATTLE_EVENT_LETHAL_HIT:
                BATTLE_TRIGGER_ENEMY_EVENT_ONCE(g_BattleCurrentEnemy->hp <= g_BattleCurrentEnemy->turn.hp_change);
                break;
        }
    }
    Battle_MergeEnemyPanels();
}

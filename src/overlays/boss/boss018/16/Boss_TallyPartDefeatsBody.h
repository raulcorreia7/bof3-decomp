/* Handles the battle events of one of boss018's three sets: at the restart begin, tallies the parts
 * that are down into the boss flags and the battle result, and finishes the battle once a result is
 * set; the restart end finishes it too. */
/* Boss_HandleBattleEvent (boss018), Boss_HandleBattleEvent2 (boss018), Boss_HandleBattleEvent3 (boss018) */
#define BOSS_TALLY_PART_DEFEATS_BODY()                            \
    switch ((u8)mode) {                                           \
        case BOSS_EVENT_RESTART_BEGIN:                            \
            if (ENEMY_COMBATANT(3).status & STATUS_KO) {          \
                g_Battle.outcome.result |= BATTLE_RESULT_VICTORY; \
            }                                                     \
            if (ENEMY_COMBATANT(4).status & STATUS_KO) {          \
                g_Battle.boss_flags |= 2;                         \
                g_BattleResult |= BATTLE_RESULT_VICTORY;          \
            }                                                     \
            if (ENEMY_COMBATANT(5).status & STATUS_KO) {          \
                g_Battle.boss_flags |= 1;                         \
                g_BattleResult |= BATTLE_RESULT_DEFEAT;           \
            }                                                     \
            if (g_BattleResult != 0) {                            \
                func_800C2AA4();                                  \
            }                                                     \
            break;                                                \
        case BOSS_EVENT_ACTION_START:                             \
            break;                                                \
        case BOSS_EVENT_TURN_END:                                 \
            break;                                                \
        case BOSS_EVENT_TICK:                                     \
            break;                                                \
        case BOSS_EVENT_EFFECTS_LOADED:                           \
            break;                                                \
        case BOSS_EVENT_RESTART_END:                              \
            func_800C2AA4();                                      \
            break;                                                \
    }

#include "battle_03.h"

/* func_801DECE0 */
MATCH void Battle_RunParty(void) {
    PartyBattler* battle_work;
    PartyBattler* next_battle_work;

    battle_work = g_BattlePartyBattlers;
    g_GameState = battle_work;
    g_Task      = battle_work;
    func_801DEEB4();

    next_battle_work = battle_work + 1;
    g_GameState      = next_battle_work;
    g_Task           = next_battle_work;
    func_801DEEB4();
    battle_work = next_battle_work + 1;

    g_GameState = battle_work;
    g_Task      = battle_work;
    func_801DEEB4();
}

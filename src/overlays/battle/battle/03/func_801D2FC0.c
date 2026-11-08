#include "battle_03.h"

MATCH void func_801D2FC0(void) {
    if (g_BattleEncounter != 0) {
        g_BossBattleEventHook(BOSS_EVENT_ACTION_START);
    }
    g_BattleStep    = 1;
    g_BattleSubStep = g_BattleActionType;
}

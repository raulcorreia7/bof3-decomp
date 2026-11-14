#include "battle_03.h"

MATCH void func_801D3050(void) {
    volatile u8* battler;
    u8           i;

    func_801D4850();
    if (g_Battle.phase.sub_step == 2 && !BATTLER_IS_PLAYER(g_Battle.active_battler)) {
        for (i = 0; i < 32; i++) {
            g_TextVariables[0][i] = 0;
        }
        i       = 0;
        battler = &g_Battle.active_battler;
        do {
            s32 row;

            row                   = *battler - 3;
            g_TextVariables[0][i] = g_BattleEnemyBattlers[row].name[i];
            i++;
        } while (i < 8);
        Battle_OpenPanel();
        Battle_QueueEvent(2, 0, 0, 45, Message_GetText(SYS_THREAD_IDLE));
    }
    g_Battle.phase.mode     = BATTLE_MODE_TURNS;
    g_Battle.phase.step     = 0;
    g_Battle.phase.sub_step = 0;
}

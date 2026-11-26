#include "battle_03.h"

MATCH void func_801D31FC(void) {
    func_801D4850();
    Battle_QueueEvent(1, 0, 0, 30, D_801EB082);
    g_BattleMessageState = 1;
    Battle_SetSlotPending(g_Battle.active_battler);
    g_BattleActiveActor->header.mode = 9;
    g_Battle.ui_step += 1;
}

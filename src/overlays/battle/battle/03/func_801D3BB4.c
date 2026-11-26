#include "battle_03.h"

MATCH void func_801D3BB4(void) {
    g_BattleActiveActor->header.mode = 0xC;
    Battle_SetSlotPending(g_Battle.active_battler);
    func_800AE2D4(g_Battle.action->unk_02);
    g_Battle.ui_step += 1;
}

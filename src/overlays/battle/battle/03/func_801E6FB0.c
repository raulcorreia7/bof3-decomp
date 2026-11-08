#include "battle_03.h"

MATCH void func_801E6FB0(void) {
    u8 slot;
    /* FAKE: row index pinned to v0 so the product takes v1; pure-C best 95.10%, a 20-minute search found nothing. */
    MATCH_REG(s32, row, "v0");
    u16 flags;
    u8  id;

    if ((g_BattleState & BATTLE_STATE_EFFECT_LOADING) &&
        ((g_BattleEffectBattler->slot == g_BattleActiveBattler) ||
         ((LOBU(g_BattleActionType) == BATTLE_ACTION_ABILITY) &&
          ((LOHU(g_BattleActionId) == ABILITY_ACCESSION) || (LOHU(g_BattleActionId) == ABILITY_TEMPTATION))))) {
        g_Task->header.mode += 1;
        return;
    }
    if (g_Task->timer == 0) {
        id = func_801E8FA8();
        if (id == GAME_NONE) {
            func_801E5988();
            return;
        }
        g_Task->unk_27 = 0xFF;
        g_Task->timer  = 0x3C;
        if (g_Task->param.unk_0B != id) {
            Actor_SelectScript(s_BattleBattlerStepIds[id]);
            g_Task->param.unk_0B = id;
        }
    } else {
        g_Task->timer -= 1;
    }
    slot = g_BattleEffectBattler->slot;
    if (BATTLER_IS_PLAYER(slot)) {
        flags = g_Game.members[slot].chr.status;
    } else {
        row   = slot - 3;
        flags = g_BattleEnemyBattlers[row].status;
    }
    if ((flags & (STATUS_BLIND | STATUS_SILENCED | STATUS_SLEEPING)) == 0) {
        g_Task->header.mode = 0;
    }
    func_801E8DD8();
    func_8014D978();
    Area_AddActor();
    if ((Battle_SlotIsBlocked(g_BattleEffectBattler->slot) & BYTE_MASK) && !ACTOR_IN_USE(*g_BattleEffectBattler)) {
        g_Task->header.mode = 0;
    }
}

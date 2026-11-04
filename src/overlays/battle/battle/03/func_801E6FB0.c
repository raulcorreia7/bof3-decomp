#include "battle_03.h"

MATCH void func_801E6FB0(void) {
    u8 slot;
    /* FAKE: row index pinned to v0 so the product takes v1; pure-C best 95.10%, a 20-minute search found nothing. */
    MATCH_REG(s32, row, "v0");
    u16 flags;
    u8  id;

    if ((g_BattleState & BATTLE_STATE_EFFECT_LOADING) &&
        ((D_801EB4E0->slot == g_BattleActingBattler) ||
         ((LOBU(g_BattleActionType) == 4) && ((LOHU(g_BattleActionId) == 0x97) || (LOHU(g_BattleActionId) == 0xE1))))) {
        g_SpadWork->step_01 += 1;
        return;
    }
    if (g_SpadWork->word_08.byte.timer_0A == 0) {
        id = func_801E8FA8();
        if (id == GAME_NONE) {
            func_801E5988();
            return;
        }
        g_SpadWork->unk_27                = 0xFF;
        g_SpadWork->word_08.byte.timer_0A = 0x3C;
        if (g_SpadWork->word_08.byte.unk_0B != id) {
            Actor_SelectScript(s_BattleBattlerStepIds[id]);
            g_SpadWork->word_08.byte.unk_0B = id;
        }
    } else {
        g_SpadWork->word_08.byte.timer_0A -= 1;
    }
    slot = LOBU(D_801EB4E0->slot);
    if (BATTLER_IS_PLAYER(slot)) {
        flags = g_BattlePartyBattlers[slot].stats.status;
    } else {
        row   = slot - 3;
        flags = D_801EB630[row].status_82;
    }
    if ((flags & (STATUS_BLIND | STATUS_SILENCED | STATUS_SLEEPING)) == 0) {
        g_SpadWork->step_01 = 0;
    }
    func_801E8DD8();
    func_8014D978();
    Area_AddActor();
    if ((Battle_SlotIsBlocked(D_801EB4E0->slot) & BYTE_MASK) && !ACTOR_IN_USE(*D_801EB4E0)) {
        g_SpadWork->step_01 = 0;
    }
}

#include "battle_03.h"

/* func_801E6FB0 */
MATCH void Battle_RunAilmentActor(void) {
    u8 slot;
    /* FAKE: row index pinned to v0 so the product takes v1; pure-C best 95.10%, a 20-minute search found nothing. */
    FAKE_REG(s32, row, "v0");
    u16 flags;
    u8  id;

    if ((g_Battle.flags & BATTLE_STATE_EFFECT_LOADING) &&
        ((g_BattleEffectBattler->slot == g_Battle.active_battler) ||
         ((LOBU(g_Battle.action_type) == BATTLE_ACTION_ABILITY) && ((LOHU(g_Battle.action_id) == ABILITY_ACCESSION) || (LOHU(g_Battle.action_id) == ABILITY_TEMPTATION))))) {
        TASK(PartyMember)->header.mode += 1;
        return;
    }
    if (TASK(PartyMember)->timer == 0) {
        id = func_801E8FA8();
        if (id == GAME_NONE) {
            Effect_Reset();
            return;
        }
        TASK(PartyMember)->unk_27 = 0xFF;
        TASK(PartyMember)->timer  = 60;
        if (TASK(PartyMember)->param.unk_0B != id) {
            Script_Select(s_BattleBattlerStepIds[id]);
            TASK(PartyMember)->param.unk_0B = id;
        }
    } else {
        TASK(PartyMember)->timer -= 1;
    }
    slot = g_BattleEffectBattler->slot;
    if (BATTLER_IS_PLAYER(slot)) {
        flags = g_Game.members[slot].chr.status;
    } else {
        row   = slot - 3;
        flags = g_BattleEnemyBattlers[row].status;
    }
    if ((flags & (STATUS_BLIND | STATUS_SILENCED | STATUS_SLEEPING)) == 0) {
        TASK(PartyMember)->header.mode = 0;
    }
    func_801E8DD8();
    Script_AnimStepLoop();
    Area_AddActor();
    if ((Battle_SlotIsBlocked(g_BattleEffectBattler->slot) & BYTE_MASK) && !ACTOR_IN_USE(*g_BattleEffectBattler)) {
        TASK(PartyMember)->header.mode = 0;
    }
}

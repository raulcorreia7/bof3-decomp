#include "battle_03.h"

/* FAKE: a second symbol forces the separate %hi/%lo load retail has. */
/* FAKE: non-volatile alias of g_Battle.action_type for the closing action-type test;
 * LOBU keeps the byte's address live in s0 across the calls (99.37%). */

/* resolves the current enemy's step, the enemy twin of func_801DFCB4:
 * clears its 0xF4 result cells, stages its stat block at D_801EC2E8, runs
 * the step for the current action type, applies the 0xF8 and 0xFA cells, marks a
 * knockout at zero hp, then advances the step.
 */
MATCH void func_801E3C14(void) {
    EnemyBattler* self;
    EnemyBattler* lock_work;
    EnemyBattler* hit_work;
    EnemyBattler* tail_work;
    u8            slot;
    u8            action_type;
    u16*          flags;
    s16*          pending;

    D_801463DA                               = 0;
    g_Battle.pending_status                  = 0;
    slot                                     = g_Task->slot;
    self                                     = g_BattleCurrentEnemy;
    D_8014639C                               = g_Task;
    g_Battle.target_record                   = &self->turn;
    g_Battle.target                          = slot;
    /* Plain pointer stores, not field stores: retail keeps each one ahead
     * of the next g_Battle.target_record reload. */
    *(s16*)((u8*)self + 0xF8)                = 0;
    *(s16*)((u32)g_Battle.target_record + 6) = 0;
    *((u8*)g_Battle.target_record + 8)       = 0;
    D_801EC2E8                               = *(BattleStatBlock*)&g_BattleCurrentEnemy->stats;
    switch (LOBU(g_Battle.action_type)) {
        case BATTLE_ACTION_ATTACK:
            g_Battle.target_record->hp_change = Battle_ApplyDamage(g_Battle.active_battler, LOBU(g_Battle.target_selector));
            break;
        case BATTLE_ACTION_ABILITY:
        case BATTLE_ACTION_ITEM:
            func_8009D198();
            break;
    }
    if (BATTLE_IS_SCRIPTED()) {
        g_BattleCurrentEnemy->unk_E4(1);
    }
    lock_work = g_BattleCurrentEnemy;
    if ((lock_work->turn.target_flags & BATTLE_HIT_HP) && lock_work->turn.hp_change == 0) {
        g_Task->header.step = 3;
        return;
    }
    if (!(g_BattleCurrentEnemy->turn.damage_flags.value & COMBATANT_FLAG_DAMAGE_ROW_PRESENT)) {
        if (LOBU(g_Battle.action_type) == BATTLE_ACTION_ATTACK) {
            func_801E2314(4);
        }
        if (LOBU(g_Battle.action_type) == BATTLE_ACTION_ITEM && !(Item_GetFlags(LOHU(g_Battle.action_id) >> 8, LOHU(g_Battle.action_id) & BYTE_MASK) & 4)) {
            func_801E2314(4);
        }
        if (LOBU(g_Battle.action_type) == BATTLE_ACTION_ABILITY && !(D_801CA718[g_Battle.action_id][0] & ABILITY_TARGET_NO_HIT_REACT)) {
            func_801E2314(4);
        }
    }
    hit_work = g_BattleCurrentEnemy;
    if (hit_work->turn.target_flags & BATTLE_HIT_HP) {
        Battle_QueueAction(hit_work->turn.hp_change, g_Task->slot);
        hit_work = g_BattleCurrentEnemy;
    }
    if (hit_work->turn.target_flags & BATTLE_HIT_AP) {
        func_800AAEBC(hit_work->turn.ap_change, g_Task->slot);
    }
    pending = &g_Battle.pending_status;
    g_BattleCurrentEnemy->status |= *pending;
    *pending = 0;
    Battle_TriggerEnemyEvents();
    tail_work = g_BattleCurrentEnemy;
    if (tail_work->turn.hp_change > 0) {
        if (tail_work->hp == 0) {
            g_Task->unk_09 = 0;
            if (g_Battle.state & BATTLE_STATE_CRITICAL) {
                GFX_AllocPaletteFade(g_Task, 0x10, 0x10, 0x10, 0);
            }
            g_BattleCurrentEnemy->status = STATUS_KO;
        } else if (BATTLE_IS_SCRIPTED()) {
            Battle_PlayEnemyCue(tail_work->unk_E8[2]);
        }
    }
    if (g_BattleCurrentEnemy->turn.hp_change < 0 || g_BattleCurrentEnemy->turn.ap_change < 0) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 6));
    }
    if (!(g_Battle.state & BATTLE_STATE_DAMAGE_APPLIED)) {
        action_type = g_BattleActionType_nv;
        if (action_type == BATTLE_ACTION_ATTACK) {
            func_800AB834();
            func_800AB910();
        }
        if (g_BattleActionType_nv == BATTLE_ACTION_ABILITY && (D_801CA71C[g_Battle.action_id].mask & 0x800)) {
            func_800AB834();
            func_800AB910();
        }
    }
    flags = &g_Battle.state;
    *flags &= ~0x80;
    func_801E30F8();
    g_Task->unk_03 += 1;
}

#include "battle_03.h"

/* FAKE: a second symbol forces the separate %hi/%lo load retail has. */
/* FAKE: non-volatile alias of g_BattleActionType for the closing action-type test;
 * LOBU keeps the byte's address live in s0 across the calls (82.97%). */

/* resolves the active party record's step: clears its 0x118 result cells,
 * stages its stat block at D_801EC2E8, runs the step for the current action type,
 * applies the 0x11C and 0x11E cells, marks a knockout at zero hp, then
 * advances the step.
 */
MATCH void func_801DFCB4(void) {
    PartyBattler* self;
    PartyBattler* stats_work;
    PartyBattler* lock_work;
    PartyBattler* hit_work;
    PartyBattler* tail_work;
    PartyBattler* check_work;
    u8            slot;
    u8            action_type;
    s16*          pending;
    u16*          flags;

    D_801463DA                             = 0;
    g_BattlePendingStatus                  = 0;
    slot                                   = g_Task->slot;
    self                                   = g_GameState;
    D_8014639C                             = g_Task;
    g_BattleTargetRecord                   = &self->turn;
    g_BattleTarget                         = slot;
    /* Plain pointer stores, not field stores: retail keeps each one ahead
     * of the next g_BattleTargetRecord reload. */
    *(s16*)((u8*)self + 0x11C)             = 0;
    *(s16*)((u32)g_BattleTargetRecord + 6) = 0;
    *((u8*)g_BattleTargetRecord + 8)       = 0;
    D_801EC2E8                             = *(BattleStatBlock*)&g_GameState->chr.stats.max_hp;
    stats_work                             = g_GameState;
    if (HAS_STATUS(*stats_work, 0x800)) {
        D_801EC2EE = 1;
    }
    if (stats_work->turn.damage_flags.value & 1) {
        D_801EC303 = (D_801EC303 + 25 >= 100) ? 100 : D_801EC303 + 25;
    }
    switch (LOBU(g_BattleActionType)) {
        case BATTLE_ACTION_ATTACK:
            g_BattleTargetRecord->hp_change = Battle_ApplyDamage(g_BattleActiveBattler, g_BattleTarget);
            break;
        case BATTLE_ACTION_ABILITY:
        case BATTLE_ACTION_ITEM:
            func_8009D198();
            break;
    }
    lock_work = g_GameState;
    if ((lock_work->turn.target_flags & 1) && lock_work->turn.hp_change == 0) {
        g_Task->header.step = 3;
        return;
    }
    if (!(g_GameState->turn.damage_flags.value & COMBATANT_FLAG_DAMAGE_ROW_PRESENT)) {
        switch (LOBU(g_BattleActionType)) {
            case BATTLE_ACTION_ITEM:
                if (!(Item_GetFlags(LOHU(g_BattleActionId) >> 8, LOHU(g_BattleActionId) & 0xFF) & 4)) {
                    func_801DF34C();
                }
                break;
            case BATTLE_ACTION_ABILITY:
                if (!(D_801CA718[g_BattleActionId][0] & 4)) {
                    func_801DF34C();
                }
                break;
            case BATTLE_ACTION_ATTACK:
                func_801DF34C();
                break;
        }
    }
    hit_work = g_GameState;
    if (hit_work->turn.target_flags & 1) {
        func_800AAC88(hit_work->turn.hp_change, g_Task->slot);
        hit_work = g_GameState;
    }
    if (hit_work->turn.target_flags & 2) {
        func_800AAEBC(hit_work->turn.ap_change, g_Task->slot);
    }
    pending   = &g_BattlePendingStatus;
    tail_work = g_GameState;
    tail_work->chr.status |= *pending;
    *pending = 0;
    if (tail_work->turn.hp_change > 0) {
        if (tail_work->chr.hp == 0) {
            if (tail_work->turn.action_flags.value & 2) {
                tail_work->chr.status |= STATUS_KO;
            } else {
                tail_work->chr.status = STATUS_KO;
            }
            if (!(g_GameState->turn.action_flags.value & 2)) {
                func_801DD858(1);
            }
            GFX_FreePaletteFadeTarget(g_Task);
        } else {
            func_801DD858(0);
        }
    }
    check_work = g_GameState;
    if (check_work->turn.hp_change < 0 || check_work->turn.ap_change < 0) {
        SND_QueueSelectionFx(0x206);
    }
    if (!(g_BattleState & BATTLE_STATE_DAMAGE_APPLIED)) {
        action_type = g_BattleActionType_nv;
        if (action_type == BATTLE_ACTION_ATTACK) {
            func_800AB834();
            func_800AB910();
        }
        if (g_BattleActionType_nv == BATTLE_ACTION_ABILITY && (D_801CA71C[g_BattleActionId].mask & 0x800)) {
            func_800AB834();
            func_800AB910();
        }
        flags = &g_BattleState;
        *flags &= ~0x80;
    }
    func_801DEDE4();
    g_Task->unk_03 += 1;
}

#include "battle_03.h"

/* FAKE: a second symbol forces the separate %hi/%lo load retail has. */
/* FAKE: non-volatile alias of g_Battle.action_type for the closing action-type test;
 * LOBU keeps the byte's address live in s0 across the calls (82.97%). */

/* resolves the active party record's step: clears its 0x118 result cells,
 * stages its stat block at D_801EC2E8, runs the step for the current action type,
 * applies the 0x11C and 0x11E cells, marks a knockout at zero hp, then
 * advances the step.
 */
MATCH void func_801DFCB4(void) {
    PartyMember* self;
    PartyMember* stats_work;
    PartyMember* lock_work;
    PartyMember* hit_work;
    PartyMember* tail_work;
    PartyMember* check_work;
    u8           slot;
    u8           action_type;
    s16*         pending;
    u16*         flags;

    D_801463DA                               = 0;
    g_Battle.pending_status                  = 0;
    slot                                     = g_Task->slot;
    self                                     = g_GameState;
    D_8014639C                               = g_Task;
    g_Battle.target_record                   = &self->u.turn;
    g_Battle.target                          = slot;
    /* Plain pointer stores, not field stores: retail keeps each one ahead
     * of the next g_Battle.target_record reload. */
    *(s16*)((u8*)self + 0x11C)               = 0;
    *(s16*)((u32)g_Battle.target_record + 6) = 0;
    *((u8*)g_Battle.target_record + 8)       = 0;
    D_801EC2E8                               = *(BattleStatBlock*)&g_Game.current->chr.stats.max_hp;
    stats_work                               = g_Game.current;
    if (HAS_STATUS(*stats_work, 0x800)) {
        D_801EC2EE = 1;
    }
    if (stats_work->u.turn.damage_flags.value & COMBATANT_FLAG_COMMAND_ENTERED) {
        D_801EC303 = (D_801EC303 + 25 >= 100) ? 100 : D_801EC303 + 25;
    }
    switch (LOBU(g_Battle.action_type)) {
        case BATTLE_ACTION_ATTACK:
            g_Battle.target_record->hp_change = Battle_ApplyDamage(g_Battle.active_battler, g_Battle.target);
            break;
        case BATTLE_ACTION_ABILITY:
        case BATTLE_ACTION_ITEM:
            func_8009D198();
            break;
    }
    lock_work = g_Game.current;
    if ((lock_work->u.turn.target_flags & BATTLE_HIT_HP) && lock_work->u.turn.hp_change == 0) {
        g_Task->header.step = 3;
        return;
    }
    if (!(g_Game.current->u.turn.damage_flags.value & COMBATANT_FLAG_DAMAGE_ROW_PRESENT)) {
        switch (LOBU(g_Battle.action_type)) {
            case BATTLE_ACTION_ITEM:
                if (!(Item_GetFlags(LOHU(g_Battle.action_id) >> 8, LOHU(g_Battle.action_id) & BYTE_MASK) & 4)) {
                    func_801DF34C();
                }
                break;
            case BATTLE_ACTION_ABILITY:
                if (!(D_801CA718[g_Battle.action_id][0] & ABILITY_TARGET_NO_HIT_REACT)) {
                    func_801DF34C();
                }
                break;
            case BATTLE_ACTION_ATTACK:
                func_801DF34C();
                break;
        }
    }
    hit_work = g_GameState;
    if (hit_work->u.turn.target_flags & BATTLE_HIT_HP) {
        Battle_QueueAction(hit_work->u.turn.hp_change, g_Task->slot);
        hit_work = g_Game.current;
    }
    if (hit_work->u.turn.target_flags & BATTLE_HIT_AP) {
        func_800AAEBC(hit_work->u.turn.ap_change, g_Task->slot);
    }
    pending   = &g_Battle.pending_status;
    tail_work = g_Game.current;
    tail_work->chr.status |= *pending;
    *pending = 0;
    if (tail_work->u.turn.hp_change > 0) {
        if (tail_work->chr.hp == 0) {
            if (tail_work->u.turn.action_flags.value & COMBATANT_FLAG_DRAGON_FORM) {
                tail_work->chr.status |= STATUS_KO;
            } else {
                tail_work->chr.status = STATUS_KO;
            }
            if (!(g_Game.current->u.turn.action_flags.value & COMBATANT_FLAG_DRAGON_FORM)) {
                func_801DD858(1);
            }
            GFX_FreePaletteFadeTarget(g_Task);
        } else {
            func_801DD858(0);
        }
    }
    check_work = g_Game.current;
    if (check_work->u.turn.hp_change < 0 || check_work->u.turn.ap_change < 0) {
        SND_QueueSelectionFx(0x206);
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
        flags = &g_Battle.state;
        *flags &= ~0x80;
    }
    func_801DEDE4();
    g_Task->unk_03 += 1;
}

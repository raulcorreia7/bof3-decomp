#include "battle_03.h"

/* FAKE: a second symbol forces the separate %hi/%lo load retail has. */
/* FAKE: non-volatile alias of g_BattleActionType for the closing mode test;
 * LOBU keeps the byte's address live in s0 across the calls (82.97%). */

/* resolves the active party record's step: clears its 0x118 result cells,
 * stages its stat block at D_801EC2E8, runs the step for the current kind,
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
    u8            mode;
    s16*          pending;
    u16*          flags;

    D_801463DA                             = 0;
    g_BattlePendingStatus                  = 0;
    slot                                   = g_SpadWork->slot;
    self                                   = g_GameState;
    D_8014639C                             = (s32)g_SpadWork;
    g_BattleTargetRecord                   = (s16*)&self->unk_118;
    g_BattleTarget                         = slot;
    /* Plain pointer stores, not field stores: retail keeps each one ahead
     * of the next g_BattleTargetRecord reload. */
    *(s16*)((u8*)self + 0x11C)             = 0;
    *(s16*)((u32)g_BattleTargetRecord + 6) = 0;
    *((u8*)g_BattleTargetRecord + 8)       = 0;
    D_801EC2E8                             = *(BattleStatBlock*)&g_GameState->stats.max_hp;
    stats_work                             = g_GameState;
    if (HAS_STATUS(*stats_work, 0x800)) {
        D_801EC2EE = 1;
    }
    if (stats_work->flags_124.value & 1) {
        D_801EC303 = (D_801EC303 + 25 >= 100) ? 100 : D_801EC303 + 25;
    }
    switch (LOBU(g_BattleActionType)) {
        case 1:
            g_BattleTargetRecord[2] = Battle_ApplyDamage(g_BattleActiveBattler, g_BattleTarget);
            break;
        case 4:
        case 5:
            func_8009D198();
            break;
    }
    lock_work = g_GameState;
    if ((lock_work->unk_120 & 1) && (s16)lock_work->hp_change == 0) {
        g_SpadWork->unk_02 = 3;
        return;
    }
    if (!(g_GameState->flags_124.value & COMBATANT_FLAG_DAMAGE_ROW_PRESENT)) {
        switch (LOBU(g_BattleActionType)) {
            case 5:
                if (!(Item_GetFlags(LOHU(g_BattleActionId) >> 8, LOHU(g_BattleActionId) & BYTE_MASK) & 4)) {
                    func_801DF34C();
                }
                break;
            case 4:
                if (!(D_801CA718[LOHU(g_BattleActionId)][0] & 4)) {
                    func_801DF34C();
                }
                break;
            case 1:
                func_801DF34C();
                break;
        }
    }
    hit_work = g_GameState;
    if (hit_work->unk_120 & 1) {
        func_800AAC88(hit_work->hp_change, g_SpadWork->slot);
        hit_work = g_GameState;
    }
    if (hit_work->unk_120 & 2) {
        func_800AAEBC(hit_work->ap_change, g_SpadWork->slot);
    }
    pending   = &g_BattlePendingStatus;
    tail_work = g_GameState;
    tail_work->stats.status |= *pending;
    *pending = 0;
    if ((s16)tail_work->hp_change > 0) {
        if (tail_work->stats.current_hp == 0) {
            if (tail_work->flags_128.value & 2) {
                tail_work->stats.status |= STATUS_KO;
            } else {
                tail_work->stats.status = STATUS_KO;
            }
            if (!(g_GameState->flags_128.value & 2)) {
                func_801DD858(1);
            }
            GFX_FreePaletteFadeTarget(g_SpadWork);
        } else {
            func_801DD858(0);
        }
    }
    check_work = g_GameState;
    if ((s16)check_work->hp_change < 0 || (s16)check_work->ap_change < 0) {
        SND_QueueSelectionFx(0x206);
    }
    if (!(g_BattleState & BATTLE_STATE_DAMAGE_APPLIED)) {
        mode = g_BattleActionType_nv;
        if (mode == 1) {
            func_800AB834();
            func_800AB910();
        }
        if (g_BattleActionType_nv == 4 && (D_801CA71C[LOHU(g_BattleActionId)].mask & 0x800)) {
            func_800AB834();
            func_800AB910();
        }
        flags = &g_BattleState;
        *flags &= ~0x80;
    }
    func_801DEDE4();
    g_SpadWork->unk_03 += 1;
}

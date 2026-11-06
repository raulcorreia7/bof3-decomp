#include "battle_03.h"

/* FAKE: a second symbol forces the separate %hi/%lo load retail has. */
/* FAKE: non-volatile alias of g_BattleActionType for the closing action-type test;
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

    D_801463DA                             = 0;
    g_BattlePendingStatus                  = 0;
    slot                                   = g_Task->slot;
    self                                   = g_BattleCurrentEnemy;
    D_8014639C                             = g_Task;
    g_BattleTargetRecord                   = (s16*)&self->command;
    g_BattleTarget                         = slot;
    *(s16*)((u8*)self + 0xF8)              = 0;
    *(s16*)((u32)g_BattleTargetRecord + 6) = 0;
    *((u8*)g_BattleTargetRecord + 8)       = 0;
    D_801EC2E8                             = *(BattleStatBlock*)&g_BattleCurrentEnemy->stats;
    switch (LOBU(g_BattleActionType)) {
        case BATTLE_ACTION_ATTACK:
            g_BattleTargetRecord[2] = Battle_ApplyDamage(g_BattleActiveBattler, LOBU(g_BattleTargetSelector));
            break;
        case BATTLE_ACTION_ABILITY:
        case BATTLE_ACTION_ITEM:
            func_8009D198();
            break;
    }
    if (g_BattleEncounter != 0) {
        g_BattleCurrentEnemy->unk_E4(1);
    }
    lock_work = g_BattleCurrentEnemy;
    if ((lock_work->target_flags & 1) && lock_work->hp_change == 0) {
        g_Task->header.step = 3;
        return;
    }
    if (!(g_BattleCurrentEnemy->damage_flags & COMBATANT_FLAG_DAMAGE_ROW_PRESENT)) {
        if (LOBU(g_BattleActionType) == BATTLE_ACTION_ATTACK) {
            func_801E2314(4);
        }
        if (LOBU(g_BattleActionType) == BATTLE_ACTION_ITEM &&
            !(Item_GetFlags(LOHU(g_BattleActionId) >> 8, LOHU(g_BattleActionId) & BYTE_MASK) & 4)) {
            func_801E2314(4);
        }
        if (LOBU(g_BattleActionType) == BATTLE_ACTION_ABILITY && !(D_801CA718[g_BattleActionId][0] & 4)) {
            func_801E2314(4);
        }
    }
    hit_work = g_BattleCurrentEnemy;
    if (hit_work->target_flags & 1) {
        func_800AAC88(hit_work->hp_change, g_Task->slot);
        hit_work = g_BattleCurrentEnemy;
    }
    if (hit_work->target_flags & 2) {
        func_800AAEBC(hit_work->ap_change, g_Task->slot);
    }
    pending = &g_BattlePendingStatus;
    g_BattleCurrentEnemy->status |= *pending;
    *pending = 0;
    Battle_TestAICondition();
    tail_work = g_BattleCurrentEnemy;
    if (tail_work->hp_change > 0) {
        if (tail_work->hp == 0) {
            g_Task->unk_09 = 0;
            if (g_BattleState & BATTLE_STATE_CRITICAL) {
                GFX_AllocPaletteFade(g_Task, 0x10, 0x10, 0x10, 0);
            }
            g_BattleCurrentEnemy->status = STATUS_KO;
        } else if (g_BattleEncounter != 0) {
            func_801E52F0(tail_work->unk_E8[2]);
        }
    }
    if (g_BattleCurrentEnemy->hp_change < 0 || g_BattleCurrentEnemy->ap_change < 0) {
        SND_PlayCue(EMI_CUE_ID(2, 6));
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
    }
    flags = &g_BattleState;
    *flags &= ~0x80;
    func_801E30F8();
    g_Task->unk_03 += 1;
}

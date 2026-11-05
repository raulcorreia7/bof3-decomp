#include "battle_03.h"

/* FAKE: non-volatile alias of g_BattleActionType for the closing mode test;
 * LOBU keeps the byte's address live in s0 across the calls (99.37%). */

/* resolves the current enemy's step, the enemy twin of func_801DFCB4:
 * clears its 0xF4 result cells, stages its stat block at D_801EC2E8, runs
 * the step for the current kind, applies the 0xF8 and 0xFA cells, marks a
 * knockout at zero hp, then advances the step.
 */
MATCH void func_801E3C14(void) {
    EnemyBattler* self;
    EnemyBattler* lock_work;
    EnemyBattler* hit_work;
    EnemyBattler* tail_work;
    u8            slot;
    u8            mode;
    u16*          flags;
    s16*          pending;

    D_801463DA                             = 0;
    g_BattlePendingStatus                  = 0;
    slot                                   = g_SpadWork->slot;
    self                                   = g_BattleCurrentEnemy;
    D_8014639C                             = (s32)g_SpadWork;
    g_BattleTargetRecord                   = (s16*)&self->pad_F1[3];
    g_BattleTarget                         = slot;
    *(s16*)((u8*)self + 0xF8)              = 0;
    *(s16*)((u32)g_BattleTargetRecord + 6) = 0;
    *((u8*)g_BattleTargetRecord + 8)       = 0;
    D_801EC2E8                             = *(BattleStatBlock*)&g_BattleCurrentEnemy->cell_A0;
    switch (LOBU(g_BattleActionType)) {
        case 1:
            g_BattleTargetRecord[2] = Battle_ApplyDamage(g_BattleActingBattler, LOBU(g_BattleTargetSelector));
            break;
        case 4:
        case 5:
            func_8009D198();
            break;
    }
    if (g_BattleEncounter != 0) {
        g_BattleCurrentEnemy->unk_E4(1);
    }
    lock_work = g_BattleCurrentEnemy;
    if ((lock_work->target_flags_FC & 1) && lock_work->damage_F8 == 0) {
        g_SpadWork->unk_02 = 3;
        return;
    }
    if (!(g_BattleCurrentEnemy->flags_100 & COMBATANT_FLAG_DAMAGE_ROW_PRESENT)) {
        if (LOBU(g_BattleActionType) == 1) {
            func_801E2314(4);
        }
        if (LOBU(g_BattleActionType) == 5 &&
            !(Item_GetFlags(LOHU(g_BattleActionId) >> 8, LOHU(g_BattleActionId) & BYTE_MASK) & 4)) {
            func_801E2314(4);
        }
        if (LOBU(g_BattleActionType) == 4 && !(D_801CA718[LOHU(g_BattleActionId)][0] & 4)) {
            func_801E2314(4);
        }
    }
    hit_work = g_BattleCurrentEnemy;
    if (hit_work->target_flags_FC & 1) {
        func_800AAC88(hit_work->damage_F8, g_SpadWork->slot);
        hit_work = g_BattleCurrentEnemy;
    }
    if (hit_work->target_flags_FC & 2) {
        func_800AAEBC(hit_work->unk_FA, g_SpadWork->slot);
    }
    pending = &g_BattlePendingStatus;
    g_BattleCurrentEnemy->status_82 |= *pending;
    *pending = 0;
    func_8009BBE8();
    tail_work = g_BattleCurrentEnemy;
    if (tail_work->damage_F8 > 0) {
        if (tail_work->hp_94 == 0) {
            g_SpadWork->word_08.byte.unk_09 = 0;
            if (g_BattleState & BATTLE_STATE_CRITICAL) {
                GFX_AllocPaletteFade(g_SpadWork, 0x10, 0x10, 0x10, 0);
            }
            g_BattleCurrentEnemy->status_82 = STATUS_KO;
        } else if (g_BattleEncounter != 0) {
            func_801E52F0(tail_work->unk_E8[2]);
        }
    }
    if (g_BattleCurrentEnemy->damage_F8 < 0 || (s16)g_BattleCurrentEnemy->unk_FA < 0) {
        SND_PlayCue(EMI_CUE_ID(2, 6));
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
    }
    flags = &g_BattleState;
    *flags &= ~0x80;
    func_801E30F8();
    g_SpadWork->unk_03 += 1;
}

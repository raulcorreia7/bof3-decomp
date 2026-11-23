#include "battle_15.h"

#ifdef NON_MATCHING
NON_MATCHING u8 Battle_CanTarget(s32 selector, u32 battler_index) {
    BattleTargetSelection* ctx;
    BattleTurn*            saved_record;
    u8*                    src;
    u8                     saved_sel;
    u8                     sel;

    ctx          = (BattleTargetSelection*)&g_Battle.target;
    saved_sel    = ctx->sel;
    saved_record = (BattleTurn*)ctx->record;
    sel          = battler_index & BYTE_MASK;
    if (BATTLER_IS_PLAYER(sel)) {
        ctx->sel    = battler_index;
        ctx->record = (s16*)&g_Game.members[sel].u.turn;
        src         = (u8*)&g_Game.members[sel].chr.stats;
    } else {
        ctx->record = (s16*)&ENEMY_COMBATANT(sel).turn;
        ctx->sel    = battler_index;
        src         = (u8*)&ENEMY_COMBATANT(sel).stats;
    }
    /* Snapshot the target's stats for the damage math. */
    *(Cpy32u*)g_BattleCalcStats = *(Cpy32u*)src;
    if (func_800A40D0(selector & BYTE_MASK) != 0) {
        g_Battle.target        = saved_sel;
        g_Battle.target_record = saved_record;
        return 0;
    }
    g_Battle.target        = saved_sel;
    g_Battle.target_record = saved_record;
    return 1;
}
#else
INCLUDE_ASM(Battle_CanTarget);
#endif

#include "battle_15.h"

#ifdef NON_MATCHING
NON_MATCHING u8 Battle_CanTarget(s32 selector, u32 battler_index) {
    BattleTargetSelection* ctx;
    FAKE_REG(BattleTargetSelection*, ctxp, "a2");
    u8*         dst;
    u8*         src;
    u32         index;
    u8          sel;
    u8          saved_sel;
    BattleTurn* saved_record;

    ctx  = (BattleTargetSelection*)&g_Battle.target;
    ctxp = ctx;
    FAKE_OPAQUE(ctxp);
    saved_sel    = ctxp->sel;
    saved_record = (BattleTurn*)ctxp->record;
    sel          = battler_index & BYTE_MASK;
    if (BATTLER_IS_PLAYER(sel)) {
        ctxp->sel    = battler_index;
        ctxp->record = (s16*)&g_Game.members[sel].u.turn;
        src          = (u8*)&g_Game.members[sel].chr.stats;
    } else {
        ctxp->record = (s16*)&ENEMY_COMBATANT(sel).turn;
        ctxp->sel    = battler_index;
        index        = sel - BATTLE_PARTY_CHARACTERS_COUNT;
        src          = (u8*)&g_BattleEnemyBattlers[index].stats;
    }
    dst           = D_801EC2E8;
    *(Cpy32u*)dst = *(Cpy32u*)src;
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

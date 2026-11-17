#include "battle_15.h"

/* func_800AED5C */
#ifdef NON_MATCHING
NON_MATCHING u8 Battle_CanTarget(s32 selector, u32 battler_index) {
    u8*         dst;
    u8*         src;
    u32         index;
    u8          sel;
    u8          saved_sel;
    BattleTurn* saved_record;
    s32         result;

    saved_sel    = g_Battle.target;
    saved_record = g_Battle.target_record;
    sel          = battler_index & BYTE_MASK;
    if (BATTLER_IS_PLAYER(sel)) {
        g_Battle.target_record = &g_Game.members[sel].u.turn;
        src                    = &D_80145F20[sel * BATTLE_PARTY_STRIDE];
        g_Battle.target        = battler_index;
    } else {
        g_Battle.target_record = &ENEMY_COMBATANT(sel).turn;
        index                  = sel - BATTLE_PARTY_CHARACTERS_COUNT;
        src                    = (u8*)&g_BattleEnemyBattlers[index].stats;
        g_Battle.target        = battler_index;
    }
    dst           = D_801EC2E8;
    *(Cpy32u*)dst = *(Cpy32u*)src;
    if (func_800A40D0(selector & BYTE_MASK) != 0) {
        result = 0;
    } else {
        result = 1;
    }
    g_Battle.target        = saved_sel;
    g_Battle.target_record = saved_record;
    return result;
}
#else
INCLUDE_ASM(Battle_CanTarget);
#endif

#include "battle_15.h"

/* 0x20-byte unaligned head record copied with lwl/lwr. */
typedef struct BattleRecordHead {
    u8 bytes[32];
} BattleRecordHead;

extern u8 D_80145F20[];

#ifdef NON_MATCHING
NON_MATCHING u8 func_800AED5C(s32 arg0, u32 battler_index) {
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
    dst                     = D_801EC2E8;
    *(BattleRecordHead*)dst = *(BattleRecordHead*)src;
    if (func_800A40D0(arg0 & BYTE_MASK) != 0) {
        result = 0;
    } else {
        result = 1;
    }
    g_Battle.target        = saved_sel;
    g_Battle.target_record = saved_record;
    return result;
}
#else
INCLUDE_ASM(func_800AED5C);
#endif

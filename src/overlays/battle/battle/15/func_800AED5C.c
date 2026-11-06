#include "battle_15.h"

/* 0x20-byte unaligned head record copied with lwl/lwr. */
typedef struct BattleRecordHead {
    u8 bytes[0x20];
} BattleRecordHead;

extern u8 D_80145F20[];
extern u8 D_801EB6D0[];

#ifdef NON_MATCHING
NON_MATCHING s32 func_800AED5C(s32 arg0, u32 battler_index) {
    BattleSelectionContext* ctx;
    u8*                     dst;
    u8*                     src;
    u8                      sel;
    u8                      saved_sel;
    u32                     saved_ptr;
    s32                     result;

    ctx       = (BattleSelectionContext*)&g_BattleTarget;
    saved_sel = ctx->sel;
    saved_ptr = (u32)ctx->record;
    sel       = battler_index & BYTE_MASK;
    if (BATTLER_IS_PLAYER(sel)) {
        src         = &D_80145F20[sel * BATTLE_PARTY_STRIDE];
        ctx->sel    = battler_index;
        ctx->record = (s16*)&D_80145FA8[sel * BATTLE_PARTY_STRIDE];
    } else {
        ctx->record = (s16*)&D_801EB3DC[sel * BATTLE_ENEMY_STRIDE];
        src         = &D_801EB6D0[(sel - 3) * BATTLE_ENEMY_STRIDE];
        ctx->sel    = battler_index;
    }
    dst                     = D_801EC2E8;
    *(BattleRecordHead*)dst = *(BattleRecordHead*)src;
    if (func_800A40D0(arg0 & BYTE_MASK) != 0) {
        result = 0;
    } else {
        result = 1;
    }
    ctx->sel    = saved_sel;
    ctx->record = (s16*)saved_ptr;
    return result;
}
#else
INCLUDE_ASM(func_800AED5C);
#endif

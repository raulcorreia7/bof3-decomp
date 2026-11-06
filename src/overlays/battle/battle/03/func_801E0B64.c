#include "battle_03.h"

/* Refreshes the per-battler substate copies and panel positions.
 */
/* nonmatching unmeasured: tried the first draft rewritten with typed word/byte copy loops. resume: close the +0x8
 * immediate/address materialization. */
#ifdef NON_MATCHING
NON_MATCHING void func_801E0B64(void) {
    u8*  src;
    u8*  dst;
    u32* src_word;
    u32* dst_word;
    s32  slot;
    s32  i;

    Char_RebuildStats(&g_Characters[g_GameState->unk_13A[2]]);
    for (slot = 0; slot < g_BattlePartyCount; slot++) {
        src = &g_Characters[g_BattlePartyBattlers[slot].character_index];
        dst = &D_80145F04[slot * BATTLE_PARTY_STRIDE];
        for (i = 14; i < 20; i++) {
            dst[i] = src[i];
        }
        dst_word = (u32*)(dst + 0x3C);
        src_word = (u32*)(src + 0x1C);
        for (i = 0; i < 8; i++) {
            dst_word[i] = src_word[i];
        }
    }
    func_800AAA74();
    for (slot = 0; slot < g_BattlePartyCount; slot++) {
        dst      = &D_80145F20[slot * BATTLE_PARTY_STRIDE];
        src      = dst + 0x20;
        dst_word = (u32*)dst;
        src_word = (u32*)src;
        for (i = 0; i < 8; i++) {
            dst_word[i] = src_word[i];
        }
    }
    func_800A4458();
    for (slot = 0; slot < g_BattlePartyCount; slot++) {
        func_800A9BD8(slot);
    }
}
#else
INCLUDE_ASM(func_801E0B64);
#endif

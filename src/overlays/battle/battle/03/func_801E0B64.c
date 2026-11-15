#include "battle_03.h"

/* Refreshes the per-battler substate copies and panel positions.
 */
#ifdef NON_MATCHING
NON_MATCHING void func_801E0B64(void) {
    u8* src;
    u8* dst;
    u8  slot;

    Char_RebuildStats(&g_Characters[g_Game.current->unk_13A[2]]);
    for (slot = 0; slot < g_Battle.party_count; slot++) {
        dst       = &D_80145F04[slot * BATTLE_PARTY_STRIDE];
        src       = &g_Characters[g_Game.members[slot].character_index];
        dst[0x0E] = src[0x0E];
        dst[0x0F] = src[0x0F];
        dst[0x10] = src[0x10];
        dst[0x11] = src[0x11];
        dst[0x12] = src[0x12];
        dst[0x13] = src[0x13];
        memcpy(dst + 0x3C, src + 0x1C, 0x20);
    }
    Battle_ApplyFormationStats();
    for (slot = 0; slot < g_Battle.party_count; slot++) {
        dst = &D_80145F20[slot * BATTLE_PARTY_STRIDE];
        memcpy(dst, dst + 0x20, 0x20);
    }
    func_800A4458();
    for (slot = 0; slot < g_Battle.party_count; slot++) {
        Battle_RescaleStats(slot);
    }
}
#else
INCLUDE_ASM(func_801E0B64);
#endif

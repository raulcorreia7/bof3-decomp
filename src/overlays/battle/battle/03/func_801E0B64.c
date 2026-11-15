#include "battle_03.h"

/* Refreshes the per-battler substate copies and panel positions.
 */
MATCH void func_801E0B64(void) {
    u8  index;
    u8  field_index;
    u8* count;
    u8* band_count;
    u8* src;
    u8* dst;

    field_index = g_Game.current->unk_13A[2];
    Char_RebuildStats(&g_Characters[field_index]);

    count = &g_BattlePartyCount;
    index = 0;
    if (*count != 0) {
        do {
            s32 offset;

            offset      = index * BATTLE_PARTY_STRIDE;
            dst         = (u8*)D_80145F04 + offset;
            field_index = D_80145FCC[offset];
            src         = (u8*)&g_Characters[field_index];
            dst[0x0E]   = src[0x0E];
            dst[0x0F]   = src[0x0F];
            dst[0x10]   = src[0x10];
            dst[0x11]   = src[0x11];
            dst[0x12]   = src[0x12];
            dst[0x13]   = src[0x13];
            memcpy(dst + 0x3C, src + 0x1C, 0x20);
            index++;
        } while (index < *count);
    }

    Battle_ApplyFormationStats();

    band_count = &g_BattlePartyCount;
    index      = 0;
    if (*band_count != 0) {
        do {
            memcpy(&D_80145F20[index * BATTLE_PARTY_STRIDE], &D_80145F20[index * BATTLE_PARTY_STRIDE + 0x20], 0x20);
            index++;
        } while (index < *band_count);
    }

    func_800A4458();

    index = 0;
    if (g_BattlePartyCount != 0) {
        do {
            Battle_RescaleStats(index);
            index++;
        } while (index < g_BattlePartyCount);
    }
}

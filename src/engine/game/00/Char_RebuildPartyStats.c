#include "game_00.h"

/* func_801C16B8 */
MATCH void Char_RebuildPartyStats(void) {
    Character* record;
    s32        count;
    s32        dst_off;
    Character* src_base;
    u8*        dst_base;
    /* FAKE: address-taken 8-byte local reserves retail's unused frame slot;
     * the pointer itself is never dereferenced. */
    u8         buffer[8];
    u8*        buffer_ptr;

    buffer_ptr = buffer;
    count      = 0;
    record     = g_Characters;
    do {
        if (g_Characters[count].unk_07 & 0x1) {
            g_Characters[count].fatigue = 0;
            Char_RebuildStats(record);
            g_Characters[count].status    = 0;
            g_Characters[count].willpower = g_Characters[count].stats.willpower;
            g_Characters[count].hp        = g_Characters[count].stats.max_hp;
            g_Characters[count].ap        = g_Characters[count].stats.max_ap;
        }
        record += 1;
        count += 1;
    } while (count < CHARACTER_COUNT);

    /* Signed gate: retail tests the party byte with blez. */
    count = 0;
    if ((s16)g_Game.party_size > 0) {
        src_base = g_Characters;
        dst_base = D_80145F04;
        dst_off  = 0;
        do {
            /* Destination offset-first addition keeps retail's addu operand order. */
            *MEM_PTR(Character, dst_off + (u32)dst_base) = src_base[g_CharSlot[g_PartyFieldOrder[count]]];
            dst_off += BATTLE_PARTY_STRIDE;
            count += 1;
        } while (count < g_PartySize);
    }
}

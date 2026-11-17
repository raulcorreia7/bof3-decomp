#include "area191_13.h"

MATCH void func_801F3AB0(void) {
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
    do {
        if (g_Characters[count].party_flags & 0x1) {
            g_Characters[count].status = 0;
            g_Characters[count].hp     = g_Characters[count].stats.max_hp;
            g_Characters[count].ap     = g_Characters[count].stats.max_ap;
        }
        count += 1;
    } while (count < CHAR_INDEX_COUNT);

    /* kept: the byte loads unsigned; the signed `> 0` test becomes `blez`. */
    count = 0;
    if ((s16)g_Game.party_size > 0) {
        src_base = g_Characters;
        dst_base = D_80145F04;
        dst_off  = 0;
        do {
            /* kept: D_80145F04 is g_Game.members[0].chr; the member form and the offset-first sum change the bytes. */
            *MEM_PTR(Character, dst_off + (u32)dst_base) = src_base[g_CharSlot[g_PartyFieldOrder[count]]];
            dst_off += BATTLE_PARTY_STRIDE;
            count += 1;
        } while (count < g_PartySize); /* kept: g_Game.party_size here adds a load. */
    }
}

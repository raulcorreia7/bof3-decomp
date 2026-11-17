#include "battle_03.h"

MATCH void func_801DCFD0(void) {
    Cpy16* src;
    Cpy16* dst;
    Cpy16* end;
    u32    index;
    s32    slot_offset;
    u8     row;

    index = 0;
    if (g_Game.party_size != 0) {
        do {
            row         = index & BYTE_MASK;
            slot_offset = row * BATTLE_PARTY_STRIDE;
            dst         = (Cpy16*)(&g_Characters[g_Game.members[row].character_index]);
            src         = (Cpy16*)(D_80145F04 + slot_offset);
            end         = (Cpy16*)(((u8*)src) + 0xA0u);
            do {
                *dst = *src;
                src += 1;
                dst += 1;
            } while (src != end);
            /* Copy the final word after the 0xA0-byte row sequence. */
            /* FAKE: the order lock holds this store in place; without it the match is 63.83%. */
            FAKE_ORDER_LOCK(*((s32*)dst) = *((s32*)src));
            index += 1;
        } while (((index & BYTE_MASK)) < (g_PartySize));
    }
}

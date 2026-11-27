#include "battle_03.h"

MATCH void func_801DCFD0(void) {
    Cpy16* src;
    Cpy16* dst;
    Cpy16* end;
    u32    index;
    s32    member_offset;
    u8     party_slot;

    index = 0;
    if (g_Game.party_size != 0) {
        do {
            party_slot    = index & BYTE_MASK;
            member_offset = party_slot * BATTLE_PARTY_STRIDE;
            dst           = (Cpy16*)(&g_Characters[g_Game.members[party_slot].character_index]);
            src           = (Cpy16*)(D_80145F04 + member_offset);
            end           = (Cpy16*)(((u8*)src) + 0xA0u);
            do {
                *dst = *src;
                src += 1;
                dst += 1;
            } while (src != end);
            /* Copy the final word after the 0xA0-byte row sequence. */
            /* FAKE: the order lock holds this store in place; without it the match is 63.83%. */
            COPY_TAIL_WORD(dst, src);
            index += 1;
        } while (((index & BYTE_MASK)) < (g_PartySize));
    }
}

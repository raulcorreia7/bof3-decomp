#include "engine/slus/slus.h"

/* adds char_id to the party order arrays D_80144F5A and D_80144F5D: below PARTY_SLOT_COUNT it appends and
 * returns 1, otherwise it replaces the first field-order member with record flag bit 1 clear that is also in the
 * battle order (1), or returns 0. Each call sets flag bits 0 and 1 on char_id's record.
 */
MATCH s32 Party_AddMember(u8 char_id) {
    s32 char_rec;
    s32 field_rec;
    s32 field_slot;
    s32 replace_slot;
    u8  field_id;
    u8  i;
    u8  j;

    char_rec                      = g_CharSlot[char_id & BYTE_MASK];
    g_Characters[char_rec].unk_07 = g_Characters[char_rec].unk_07 | 0x3;
    i                             = 0;
    if (g_PartySize < PARTY_SLOT_COUNT) {
        D_80144F5A[g_PartySize] = char_id;
        D_80144F5D[g_PartySize] = char_id;
        g_PartySize++;
        return 1;
    }
    do {
        field_slot = i & BYTE_MASK;
        field_id   = D_80144F5A[field_slot];
        field_rec  = g_CharSlot[field_id];
        if (!(g_Characters[field_rec].unk_07 & 0x2)) {
            j            = 0;
            /* Copy kept live across the battle-order search. */
            replace_slot = field_slot;
            do {
                if (field_id == D_80144F5D[j]) {
                    D_80144F5A[replace_slot] = char_id;
                    D_80144F5D[j]            = char_id;
                    return 1;
                }
                j++;
            } while (j < PARTY_SLOT_COUNT);
        }
        i++;
    } while (i < PARTY_SLOT_COUNT);
    return 0;
}

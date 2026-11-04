#include "engine/slus/slus.h"

/* selects the 3-byte record `record_index & 0xFF` from the work-area resource header; unless work flag bit 1 is set
 * it queues the palette pair and tile pointer in the next slot, then stores the record's draw offset and sub-table
 * pointer.
 */
MATCH void Actor_SelectScriptBank(u32 record_index) {
    /* FAKE: retail reserves 16 bytes of frame that no statement uses. */
    STACK_PADS(u8, 16);
    Actor* work;
    u8*    header;
    u8*    entry;
    u8*    base8;
    u8*    base0;
    u8     level;

    work   = g_SpadWork;
    header = (u8*)work->unk_4C;
    base0  = header + ((s32*)header)[0];
    base8  = header + ((s32*)header)[2];
    entry  = header + ((s32*)header)[3] + (record_index & BYTE_MASK) * 3;
    if (!(work->flags_00 & ACTOR_FLAG_SKIP_PALETTE_STAGE)) {
        level = work->unk_25;
        if (level > 16) {
            D_80145A54[D_80145A00]    = (level - 0x10) << 6;
            (&D_80145A7C)[D_80145A00] = work->unk_26 + 0x100;
        } else {
            D_80145A54[D_80145A00]    = level << 6;
            (&D_80145A7C)[D_80145A00] = work->unk_26;
        }
        (&D_80145A04)[D_80145A00] = (s32)(base0 + ((u32*)base0)[entry[0]]);
        D_80145A00++;
    }
    g_SpadWork->unk_2A    = entry[2];
    g_SpadWork->source_50 = base8 + ((u16*)base8)[entry[1]];
}

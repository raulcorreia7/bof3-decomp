#include "engine/slus/slus.h"

/* Selects the sprite bank record `record_index & 0xFF`: a 3-byte (sheet, animation, mirror) triple after header[3]
 * (a bank holds no record count; zero padding ends the list). Unless work flag bit 1 is set it queues the upload
 * of the record's sheet to texture page +0x25 and row +0x26, then stores the mirror byte (+0x2A) and the animation
 * step list (+0x50).
 */
MATCH void Actor_SelectSprite(u32 record_index) {
    /* FAKE: retail reserves 16 bytes of frame that no statement uses. */
    FAKE_STACK_PADS(u8, 16);
    Actor* work;
    u8*    header;
    u8*    entry;
    u8*    base8;
    u8*    base0;
    u8     level;

    work   = g_Task;
    header = (u8*)work->unk_4C;
    base0  = header + ((s32*)header)[0];
    base8  = header + ((s32*)header)[2];
    entry  = header + ((s32*)header)[3] + (record_index & BYTE_MASK) * 3;
    if (!(work->header.flags & ACTOR_FLAG_SKIP_PALETTE_STAGE)) {
        level = work->unk_25;
        if (level > 16) {
            D_80145A54[D_80145A00]    = (level - 0x10) << 6;
            (&D_80145A7C)[D_80145A00] = work->unk_26 + 0x100;
        } else {
            D_80145A54[D_80145A00]    = level << 6;
            (&D_80145A7C)[D_80145A00] = work->unk_26;
        }
        (&D_80145A04)[D_80145A00] = (base0 + ((u32*)base0)[entry[0]]);
        D_80145A00++;
    }
    g_Task->unk_2A = entry[2];
    g_Task->script = base8 + ((u16*)base8)[entry[1]];
}

#include "engine/slus/slus.h"

/* resolves one loader entry from its packed key, skips flagged
 * slots, and latches the base and scaled entry bounds.
 */
MATCH void SND_ResolveXaStream(s32 stream_id) {
    s32  scale;
    u8*  counter;
    u16* entry;
    s32  count;
    s32  limit;
    s32  index;
    s32  base;
    /* FAKE: bound stays in v1. */
    MATCH_FAKE_PIN(s32, bound, "v1");
    s32 second_offset;
    /* FAKE: address-taken 8-byte local reserves retail's unused frame slot;
     * the pointer itself is never dereferenced. */
    u8  buffer[8];
    u8* buffer_ptr;
    /* FAKE: extra stays in a1. */
    MATCH_FAKE_PIN(s32, extra, "a1");
    /* FAKE: flag pointer stays in a2. */
    MATCH_FAKE_PIN(volatile u8*, flag, "a2");

    buffer_ptr = buffer;
    scale      = ((stream_id >> 12) != 0) ? 0x10 : 8;
    counter    = &D_80146835;
    *counter   = 0;
    entry      = (u16*)D_8018323C[stream_id >> 12];
    count      = stream_id & 0xFFF;
    index      = 0;
    if (count > 0) {
        limit = count;
        do {
            if (*entry & 0x8000) {
                entry += 1;
                *counter += 1;
            }
            index += 1;
            entry += 1;
        } while (index < limit);
    }
    flag  = &D_80146834;
    *flag = 1;
    /* FAKE: force the flag base back into a2. */
    CLOBBER_A2();
    base                 = g_EmiSlotLbas[D_80183230[stream_id >> 12]];
    D_80146810           = base;
    *(s32*)(flag - 0x28) = base;
    extra                = flag[1];
    bound                = base + (((*entry & 0x7FFF) * scale) + extra);
    *(s32*)(flag - 0x28) = bound;
    /* FAKE: hold the second entry read after the first bound store. */
    MATCH_FAKE_BARRIER();
    second_offset = (((entry[1] & 0x7FFF) * scale) + extra);
    base -= 0x96;
    *(s32*)(flag - 0x20) = bound;
    D_80146810           = base + second_offset;
}

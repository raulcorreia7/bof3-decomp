#include "engine/slus/slus.h"

/* selects the stream record_index `record_index` through func_8014DC08, copies
 * `size` bytes from the work-area cursor to the staging buffer advanced by
 * size * the work-area byte at +0x05, then leaves the cursor at the copy end.
 */
MATCH void Actor_CopyScriptRecord(u32 record_index, u8* staging, u32 size) {
    /* FAKE: unused frame, 8 bytes. */
    FAKE_STACK_PADS(u8, 8);
    u8* dst;
    s32 count;
    s32 size;
    s32 i;

    Actor_SelectSprite(record_index & BYTE_MASK);
    count = size & HALF_MASK;
    size  = count * g_Task->unk_05;
    dst   = staging + size;
    i     = 0;
    if (count != 0) {
        do {
            dst[i] = g_Task->script[i];
            i++;
        } while (i < count);
    }
    g_Task->script = dst;
}

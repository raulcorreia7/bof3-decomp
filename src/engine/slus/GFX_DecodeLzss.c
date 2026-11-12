#include "engine/slus/slus.h"

/* The decoder's scratchpad ring: 512 bytes, entered LZSS_MAX_MATCH bytes before its end. */
#define LZSS_RING_SIZE  512
#define LZSS_MAX_MATCH  18
#define LZSS_RING_START (LZSS_RING_SIZE - LZSS_MAX_MATCH)
#define LZSS_RING_MASK  (LZSS_RING_SIZE - 1)

/* decodes the LZSS stream after the packed record's first word
 * (512-byte scratchpad ring starting at 494, 12-bit positions, 3-18 byte
 * copies) into the shared image cursor, then uploads the result and advances
 * the cursor past the aligned block.
 */
MATCH void GFX_DecodeLzss(u32* packed, RECT rect) {
    u8* src;
    u8* dst;
    u8* ring;
    u32 count;
    u32 written;
    s16 flags;
    s32 r;
    s32 i;
    s32 len;
    s32 k;
    u8  c;

    written = 0;
    src     = (u8*)(packed + 1);
    dst     = (u8*)D_801459FC;
    ring    = SP_PTR(u8, 0);
    count   = rect.w * rect.h * 2;
    for (i = LZSS_RING_START - 1; i >= 0; i--) {
        ring[i] = 0;
    }
    r     = LZSS_RING_START;
    flags = 0;
    while (written < count) {
        flags = (u16)flags >> 1;
        if (!(flags & 0x100)) {
            c     = *src++;
            flags = c;
            flags |= 0xFF00;
        }
        if (flags & 0x1) {
            /* FAKE: the order lock steers regalloc */
            FAKE_ORDER_LOCK_BEGIN
                c = *src++;
                written++;
                *dst++    = c;
                ring[r++] = c;
                r &= LZSS_RING_MASK;
            FAKE_ORDER_LOCK_END;
        } else {
            i   = *src++;
            len = *src++;
            i |= (len & 0xF0) << 4;
            len = (len & 0xF) + 2;
            for (k = 0; k <= len; k++) {
                written++;
                c         = ring[(i + k) & LZSS_RING_MASK];
                *dst++    = c;
                ring[r++] = c;
                r &= LZSS_RING_MASK;
            }
        }
    }
    LoadImage(&rect, (u_long*)D_801459FC);
    if (count & 0x3) {
        count += 4 - count % 4;
    }
    D_801459FC += count;
}

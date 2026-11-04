#include "engine/slus/slus.h"

/* decodes the LZSS stream after the packed record's first word
 * (512-byte scratchpad ring starting at 0x1EE, 12-bit positions, 3-18 byte
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
    for (i = 0x1ED; i >= 0; i--) {
        ring[i] = 0;
    }
    r     = 0x1EE;
    flags = 0;
    while (written < count) {
        flags = (u16)flags >> 1;
        if (!(flags & 0x100)) {
            c     = *src++;
            flags = c;
            flags |= 0xFF00;
        }
        if (flags & 1) {
            /* FAKE: do-while(0) scope steers regalloc */
            do {
                c = *src++;
                written++;
                *dst++    = c;
                ring[r++] = c;
                r &= 0x1FF;
            } while (0);
        } else {
            i   = *src++;
            len = *src++;
            i |= (len & 0xF0) << 4;
            len = (len & 0xF) + 2;
            for (k = 0; k <= len; k++) {
                written++;
                c         = ring[(i + k) & 0x1FF];
                *dst++    = c;
                ring[r++] = c;
                r &= 0x1FF;
            }
        }
    }
    LoadImage(&rect, (u_long*)D_801459FC);
    if (count & 3) {
        count += 4 - count % 4;
    }
    D_801459FC += count;
}

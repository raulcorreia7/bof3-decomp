#include "engine/slus/slus.h"

/* HAND_ASM: operands in `$s4`/`$s5`/`$t3`. */
#ifdef NON_MATCHING
/* C model, checked on the host by tools/tests/test_lz77_model.py: stream copy kernel.
 * copies count bytes forward, byte by byte, from src to dst, so an
 * overlapping range replicates the back-reference pattern, and returns the
 * advanced destination.
 * The original takes its operands in the entry-live register file ($s4 =
 * count, $s5 = src, $t3 = dst) with $s2 = 0x20 as the block size and $s3 =
 * 0x8016432C as the unrolled-entry table, and returns nothing. Each block
 * iteration copies 32 bytes; a sub-32 tail shifts both pointers back by
 * 32 - count and enters the unrolled block at byte 32 - count, so the tail
 * costs no loop. That register convention and the computed entry are why the
 * function stays assembly.
 */
HAND_ASM u8* func_801642F4(u8* dst, const u8* src, u32 count) {
    u32 n;

    while (count >= 32) {
        for (n = 0; n < 32; n++) {
            *dst++ = *src++;
        }
        count -= 32;
    }
    for (n = 0; n < count; n++) {
        *dst++ = *src++;
    }
    return dst;
}
#else
INCLUDE_ASM(func_801642F4);
#endif

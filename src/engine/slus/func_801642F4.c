#include "engine/slus/slus.h"

/* FAKE: proven asm-original.
 * PROFILE: no exact C match in 56 candidates each for GCC 2.8.0, 2.8.1 and
 * 2.95.2 against the 0x4D0-byte span that included func_801644D8; 2.8.x each
 * had 3 profile build errors, while 2.95.2 compiled all 56. See
 * docs/toolchain.md#compiler-chain.
 * MACHINE: entry operands are `$s4`/`$s5`/`$t3`; `$s2`/`$s3` hold block size
 * and table base. `jr $t7` enters a 12-byte-stride unrolled copy block. This
 * non-ABI entry and computed resume table are not expressible in pure C89.
 * Span 0x801642F4-0x801644D8 (0x1e4 bytes); 0x801644D8 is a separate
 * function (ten callers in the battle and shop overlays).
 * MODEL: keep the C89 semantic model below and count separately from C matches.
 */
#ifdef NON_MATCHING
/* INFERRED C model: stream copy kernel.
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
NON_MATCHING u8* func_801642F4(u8* dst, const u8* src, u32 count) {
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

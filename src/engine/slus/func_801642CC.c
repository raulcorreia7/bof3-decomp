#include "engine/slus/slus.h"

/* FAKE: proven asm-original.
 * PROFILE: no exact C match in 56 candidate profiles each for GCC 2.8.0,
 * 2.8.1 and 2.95.2; 2.8.0/2.8.1 each had 3 profile build errors, while 2.95.2
 * compiled all 56. See docs/toolchain.md#compiler-chain
 * (restore-tail-c).
 * MACHINE: entry 0x801642CC reloads `$s1`; the shared entry 0x801642D0 skips
 * it. Both rely on caller-held `$t0` context and `$s6` saved-return state.
 * This non-ABI multi-entry restore tail has no C89 function equivalent.
 * MODEL: keep the no-op C89 model below and count this separately from C.
 */
#ifdef NON_MATCHING
/* INFERRED C model: shared restore tail of the resumable decoder.
 * reloads the outer caller's $s1-$s7 from the context spill area at
 * 0x800327A0 + 0x20..0x3C and returns through the return address parked in
 * $s6. Entry 0x801642D0 is the same tail without the $s1 reload; the 0xFF exit
 * of LZ77_DecodeStep enters there and reloads $s1 itself, which is why the tail
 * has two entry points.
 * The function has no memory effects: its entire body is the register reload
 * plus the return, and a C epilogue is compiler-owned, so the model has no
 * statements of its own.
 */
NON_MATCHING void func_801642CC(void) {
    /* Register restore and return; see the comment above. */
}
#else
INCLUDE_ASM(func_801642CC);
#endif

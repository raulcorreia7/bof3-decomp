#include "engine/slus/slus.h"

/* HAND_ASM: multi-entry register-restore tail (0x801642CC reloads `$s1`, 0x801642D0 skips it) over
 * caller-held `$t0` and `$s6`; C89 has no equivalent. See docs/toolchain.md#compiler-chain. */
#ifdef NON_MATCHING
/* INFERRED C model: shared restore tail of the resumable decoder.
 * reloads the outer caller's $s1-$s7 from the context spill area at
 * 0x800327A0 + 0x20..0x3C and returns through the return address parked in
 * $s6. Entry 0x801642D0 is the same tail without the $s1 reload; the 0xFF exit
 * of EMI_DecodeStep enters there and reloads $s1 itself, which is why the tail
 * has two entry points.
 * The function has no memory effects: its entire body is the register reload
 * plus the return, and a C epilogue is compiler-owned, so the model has no
 * statements of its own.
 */
HAND_ASM void func_801642CC(void) {
    /* Register restore and return; see the comment above. */
}
#else
INCLUDE_ASM(func_801642CC);
#endif

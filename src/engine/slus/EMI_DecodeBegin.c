#include "engine/slus/slus.h"

/* FAKE: origin unresolved.
 * PROFILE: the prior 52-profile catalog and the new 56-profile matrices for
 * GCC 2.8.0, 2.8.1 and 2.95.2 found no exact C match. Both a plain C89 form and
 * a `register`/`ori` address form were tested; the best output is still 60
 * bytes with differences. See docs/toolchain.md#compiler-chain.
 * MACHINE: this is an ordinary ABI leaf (`$a0` input, `$ra` return). Its
 * `$t0`-`$t2` allocation and `lui`/`ori` addresses are compiler-emittable.
 * No non-ABI entry, live-across-call caller register or computed resume entry
 * proves hand authorship.
 * OPEN: do not count this as `asm-original`. Keep the byte-preserving assembly
 * branch until C89 matches or provenance supplies proof; the model below
 * documents the inferred behavior.
 */
#if BOF3_USE_ASM
MATCH INCLUDE_ASM(EMI_DecodeBegin);
#else
/* INFERRED C model: initialises the resumable stream decoder described by
 * EMI_DecodeStep.
 * records the decompression destination, points the input cursor 6
 * bytes into the scratchpad (the first sector's stream starts after its 6-byte
 * prefix; later refills restart at the base), stores the scratchpad window end
 * and the copy-kernel resume entry, and clears the resume state.
 * The original is a leaf that keeps the context base in $t0 and writes every
 * field through `ori` li-form addresses; C89 cannot hold a fixed address in a
 * register across the stores.
 */
void EMI_DecodeBegin(u8* dst) {
    EmiDecodeContext* ctx;

    ctx             = D_800327A0;
    ctx->dst        = dst;
    ctx->src        = (u8*)(SCRATCH_PAD + 6);
    ctx->limit      = (u8*)(SCRATCH_PAD + SCRATCH_PAD_SIZE);
    ctx->copy_entry = (u8*)COPY_KERNEL_ENTRY;
    ctx->state      = 0;
    ctx->unk0C      = 0;
}
#endif

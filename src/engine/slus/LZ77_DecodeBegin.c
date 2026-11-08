#include "engine/slus/slus.h"

/* HAND_ASM: leaf with `$t0`-`$t2` allocation and `ori` addresses no profile reproduces.
 * See docs/toolchain.md#compiler-chain. */
#ifdef NON_MATCHING
/* INFERRED C model: initialises the resumable stream decoder described by
 * LZ77_DecodeStep.
 * records the decompression destination, points the input cursor 6
 * bytes into the scratchpad (the first sector's stream starts after its 6-byte
 * prefix; later refills restart at the base), stores the scratchpad window end
 * and the copy-kernel resume entry, and clears the resume state.
 * The original is a leaf that keeps the context base in $t0 and writes every
 * field through `ori` li-form addresses; C89 cannot hold a fixed address in a
 * register across the stores.
 */
HAND_ASM void LZ77_DecodeBegin(u8* dst) {
    EMIDecodeContext* ctx;

    ctx             = D_800327A0;
    ctx->dst        = dst;
    ctx->src        = (u8*)(SCRATCH_PAD + 6);
    ctx->limit      = (u8*)(SCRATCH_PAD + SCRATCH_PAD_SIZE);
    ctx->copy_entry = (u8*)COPY_KERNEL_ENTRY;
    ctx->state      = 0;
    ctx->unk0C      = 0;
}
#else
INCLUDE_ASM(LZ77_DecodeBegin);
#endif

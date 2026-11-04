#include "engine/slus/slus.h"

/* FAKE: proven asm-original.
 * PROFILE: no exact C match in 56 candidate profiles each for GCC 2.8.0,
 * 2.8.1 and 2.95.2; 2.8.0/2.8.1 each had 3 profile build errors, while 2.95.2
 * compiled all 56. See docs/toolchain.md#compiler-chain
 * (decoder-clean and decoder-pinned-context-cursors).
 * MACHINE: `$t0`/`$t3` stay live across calls; `$ra` is parked in `$s6`;
 * `$s0`-`$s7` are saved in the context; `jr $t4` dispatches through an absolute
 * resume table. These non-ABI registers and computed entries are not expressible
 * in pure C89.
 * MODEL: retain the C89 model below and count this separately from C matches.
 */
#if BOF3_USE_ASM
MATCH INCLUDE_ASM(EMI_DecodeStep);
#else
/* INFERRED C model: resumable stream decoder.
 * decodes the scratchpad window [src, limit) into ctx->dst until the
 * window runs out or the 0xFF control byte appears, saving a resume state so
 * the caller can refill the window and call again. Control bytes:
 *   0x10-0x1F  literal run of 0x20 - (ctrl & 0x1F) bytes, extended by one
 *              length byte when the count is 16
 *   others     back-reference: distance 0x800 - (((ctrl & 0xE0) << 3) | byte),
 *              length (ctrl & 0x0F) + 3, extended by one length byte at 15
 *   0xFF       marker: return 15 with the saved cursors untouched
 * Returns 0 when the window ran out (resume state saved) or 15 on the marker;
 * the caller ignores the result. The original parks $ra in $s6, spills s0-s7
 * into the context, dispatches through the absolute case-address table at
 * 0x801640C0, and returns through the shared restore tail
 * 0x801642CC/0x801642D0.
 *
 * Checked against the retail body: the 0x10 control split (0x801640E4), the
 * literal length 0x20 - (ctrl & 0x1F) and its 16-byte extension
 * (0x8016420C-0x80164244), the match length (ctrl & 0x0F) + 3 and its 15-byte
 * extension (0x80164170-0x801641A4), the back-reference
 * dst + (((ctrl & 0xE0) << 3 | distance) - 0x800) (0x80164158), the five
 * resume entries, and the three save points all agree with this model.
 */
/* Resume states; the original stores state * 4 as a byte offset into the
 * absolute case-address table at 0x801640C0. */
typedef enum DecoderState {
    DECODER_MAIN           = 0,  /* read a fresh control byte */
    DECODER_MATCH_OFFSET   = 4,  /* control byte saved; distance byte pending */
    DECODER_LITERAL_TAIL   = 8,  /* literal run cut short by the window end */
    DECODER_MATCH_LENGTH   = 12, /* long match; length byte pending */
    DECODER_LITERAL_LENGTH = 16  /* 16-byte literal; length byte pending */
} DecoderState;

/* Copy kernel: copies count bytes forward and returns the advanced
 * destination. The original takes count/src/dst in $s4/$s5/$t3. */

s32 EMI_DecodeStep(void) {
    EmiDecodeContext* ctx;
    u8*               dst;
    u8*               src;
    u8*               limit;
    u8*               match;
    u32               ctrl;
    u32               len;

    ctx   = D_800327A0;
    dst   = ctx->dst;
    src   = ctx->src;
    limit = ctx->limit;

    switch (ctx->state) {
        case DECODER_MATCH_OFFSET:
            src  = (u8*)SCRATCH_PAD;
            ctrl = ctx->pending;
            goto match_offset; /* resume with the saved control byte */
        case DECODER_LITERAL_TAIL:
            /* the remainder of a literal run: the original copies it straight from
             * the refilled window without re-checking the limit */
            src = (u8*)SCRATCH_PAD;
            len = ctx->pending;
            dst = func_801642F4(dst, src, len);
            src += len;
            ctx->state = DECODER_MAIN;
            goto window_check; /* shared window-end test */
        case DECODER_MATCH_LENGTH:
            src   = (u8*)SCRATCH_PAD;
            match = ctx->src;
            len   = 15 + *src++;
            goto copy_match; /* resume with the long match length */
        case DECODER_LITERAL_LENGTH:
            src = (u8*)SCRATCH_PAD;
            len = 16 + *src++;
            goto literal_run; /* resume with the long literal length */
        default:
            break;
    }

main_loop:
    ctrl = *src++;
    if ((ctrl & LZ77_CONTROL_LITERAL_FLAG) != 0) {
        if (ctrl == 0xFF) {
            return 15;
        }
        len = 0x20 - (ctrl & LZ77_CONTROL_LITERAL_LENGTH_MASK);
        if (len == 16) {
            if (src == limit) {
                ctx->dst   = dst;
                ctx->state = DECODER_LITERAL_LENGTH;
                return 0;
            }
            len += *src++;
        }
        goto literal_run; /* shared literal copy */
    }

    if (src == limit) {
        ctx->pending = ctrl;
        ctx->dst     = dst;
        ctx->state   = DECODER_MATCH_OFFSET;
        return 0;
    }

match_offset:
    match = dst + (s32)((((u32)(ctrl & LZ77_CONTROL_MATCH_DISTANCE_MASK) << 3) | *src++) - 0x800u);
    len   = ctrl & LZ77_CONTROL_MATCH_LENGTH_MASK;
    if (len == 15) {
        if (src == limit) {
            ctx->src   = match;
            ctx->dst   = dst;
            ctx->state = DECODER_MATCH_LENGTH;
            return 0;
        }
        len += *src++;
    }

copy_match:
    dst = func_801642F4(dst, match, len + 3);
    goto window_check; /* shared window-end test */

literal_run:
    if (len > (u32)(limit - src)) {
        ctx->pending = len - (u32)(limit - src);
        len          = (u32)(limit - src);
        if (src != limit) {
            dst = func_801642F4(dst, src, len);
        }
        ctx->dst   = dst;
        ctx->state = DECODER_LITERAL_TAIL;
        return 0;
    }
    dst = func_801642F4(dst, src, len);
    src += len;
    ctx->state = DECODER_MAIN; /* the original clears the state here, mid-loop */

window_check:
    if (src != limit) {
        goto main_loop; /* the window still has input */
    }
    ctx->dst   = dst;
    ctx->state = DECODER_MAIN;
    ctx->src   = (u8*)SCRATCH_PAD;
    return 0;
}
#endif

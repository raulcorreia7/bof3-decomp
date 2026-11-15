#ifndef SYSTEM_EXE_H
#define SYSTEM_EXE_H

#include "types.h"

extern u8 g_PartyFieldOrder[];

/* Forwards the selector byte to func_8014D6DC with a zero extra operand.
 * The retail masks the argument with 0xFF before the call
 * (`andi $a0, $a0, 0xFF`, exe/slus_004_22@0x8014D6C0), so the byte is the
 * whole first argument.
 *
 * The function reads no second argument: the callee overwrites $a1 with its
 * own zero operand. Most retail callers never write $a1 before the call and
 * leave the register as they found it, so the prototype carries one
 * argument.
 *
 * Two callers do write $a1 first, for their own reasons: emi/etc/game/00
 * func_8019A3FC leaves the work pointer there and emi/battle/battle/15
 * func_800AEF98 leaves its own payload word. Their $a1 is caller context and
 * not part of this function's contract, so they call EXE_Func8014D6B8 through
 * the local macro EXE_CALL_8014D6B8, which names their own two-argument
 * form. */
/* Claims a free field record and fills its header; returns the slot, or 0xFF when none is free.
 * Retail callers pass whole words, while the callee narrows its own arguments, so the declaration
 * stays unprototyped and each caller keeps its argument widths. */
/* func_8015CB18 */
s32 Actor_ClaimSlot();
/* Draws a four-strip textured panel fill.
 *
 * The retail callee takes six words and uses the first four as full 32-bit
 * values: it copies $a0..$a3 into $s3, $s1, $s5 and $s4
 * (emi/etc/game/00@0x801AE40C) and stores the first two as halfwords
 * (`sh $s3, 0x8($s0)`). The fifth argument arrives on the stack and is read
 * as a word (`lw $v0, 0x58($sp)`) and then stored as a byte; the sixth is
 * read as a byte (`lbu $s7, 0x5C($sp)`).
 *
 * The first two are the panel's x and y. The callers mask them to 16 bits
 * before the call (`andi $a0, $a0, 0xFFFF`, emi/etc/shop/00@0x801DA324), so
 * the prototype keeps them halfwords and the masking stays in the caller.
 * The third and fourth are the panel's width and height, the fifth carries
 * the style byte whose low nibble selects the colour, and the sixth is the
 * primitive's flag byte.
 *
 * The last two are words on the caller's stack, not bytes: the retail caller
 * loads the flag byte and stores it whole
 * (`sw $v0, 0x14($sp)`, emi/etc/start/08@0x801DDD24), and the callee reads
 * the low byte of the sixth (`lbu $s7, 0x5C($sp)`). */

#endif

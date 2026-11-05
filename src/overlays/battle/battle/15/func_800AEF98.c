#include "battle_15.h"

/* The retail leaves this unit's payload word in $a1 at the call. The callee
 * overwrites $a1 with its own zero operand, so the value is caller context
 * and not part of the shared one-argument prototype in include/sys/exe.h.
 * The alias names the same address with the second argument spelled out, so
 * the compiler keeps the $a1 write. The widths are the ones this caller
 * already used: a plain word for the selector and a plain word for the
 * payload. */
#if defined(MATCHING)
asm(".globl Actor_SelectScript_keep_a1\n.set Actor_SelectScript_keep_a1, Actor_SelectScript\n");
#endif

/* swaps the scratchpad work pointer (0x1F800044) for the active battle work record, then advances its +0x08
 * byte through Actor_SelectScript or, for kind 3 and above, forwards the kind and payload through func_801E24F8; restores
 * the pointer.
 * NOTE: the kind byte is read through a plain (non-volatile) MEM view; a
 * volatile u8 load into the widened local emits a redundant `andi 0xFF` that
 * the original bytes do not have.
 */
MATCH void func_800AEF98(s32 step, s32 payload) {
    u8* work;
    u8* saved;
    u32 kind;

    work  = (u8*)D_801EB4E0;
    saved = TASK_BYTES;
    kind  = *(u8*)&g_BattleActiveBattler;
    TASK_SET(work);
    if (kind < 3u) {
        Actor_SelectScript_keep_a1((step + work[8]) & BYTE_MASK, payload);
    } else {
        func_801E24F8(kind, payload & BYTE_MASK);
    }
    TASK_SET(saved);
}

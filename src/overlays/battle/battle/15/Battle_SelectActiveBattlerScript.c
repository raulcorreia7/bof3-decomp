#include "battle_15.h"

/* The retail leaves this unit's payload word in $a1 at the call. The callee
 * overwrites $a1 with its own zero operand, so the value is caller context
 * and not part of the shared one-argument prototype in include/sys/exe.h.
 * The alias names the same address with the second argument spelled out, so
 * the compiler keeps the $a1 write. The widths are the ones this caller
 * already used: a plain word for the selector and a plain word for the
 * payload. */
#if defined(MATCHING)
asm(".globl Actor_SelectScript_keep_a1\n.set Actor_SelectScript_keep_a1, Script_Select\n");
#endif

/* swaps the scratchpad work pointer (0x1F800044) for the active battle work record, then advances its +0x08 byte
 * through Script_Select or, for type 3 and above, forwards the type and payload through func_801E24F8; restores
 * the pointer. NOTE: the type byte is read through a plain (non-volatile) MEM view; a volatile u8 load into the widened
 * local emits a redundant `andi 0xFF` that the original bytes do not have. */
/* func_800AEF98 */
MATCH void Battle_SelectActiveBattlerScript(s32 step, s32 payload) {
    u8*   work;
    void* saved;
    u32   type;

    work  = (u8*)g_BattleEffectBattler;
    saved = TASK(void);
    type  = g_Battle.active_battler;
    TASK_SET(work);
    if (type < 3u) {
        Actor_SelectScript_keep_a1((step + ((PartyMember*)work)->facing) & BYTE_MASK, payload);
    } else {
        func_801E24F8(type, payload & BYTE_MASK);
    }
    TASK_SET(saved);
}

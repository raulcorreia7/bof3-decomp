#include "battle_03.h"

/* when local-work flag 0x2000 is clear, drops the 0x70 and 0x200
 * status bits, clears the active battler's pending bit, and restarts the local
 * presentation at substate 2.
 */
MATCH void func_801E13B8(void) {
    PartyBattler*          work;
    volatile PartyBattler* cell;
    u32                    flags;
    u32                    masked;

    work  = g_GameState;
    flags = work->u.turn.damage_flags.value;
    if ((flags & 0x2000u) == 0u) {
        cell   = g_Task;
        masked = flags & ~0x70u;
        masked &= ~0x200u;
        work->u.turn.damage_flags.value = masked;
        Battle_ClearSlotPending(cell->slot);
        g_Task->header.mode = 2;
        g_Task->header.step = 0;
        g_Task->unk_03      = 0;
        g_Task->unk_04      = 0;
    }
}

#include "battle_03.h"

/* Clears the active battler's pending bit and two local-work flag masks, then resets the state bytes. */
MATCH void func_801E1050(void) {
    PartyBattler* work;

    Battle_ClearSlotPending(g_Task->slot);
    work                  = g_GameState;
    work->flags_124.value = work->flags_124.value & ~0xF0u;
    work->flags_124.value = work->flags_124.value & ~0x200u;
    g_Task->mode          = 3;
    g_Task->step          = 0;
    g_Task->unk_03        = 0;
}

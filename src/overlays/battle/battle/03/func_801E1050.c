#include "battle_03.h"

/* Clears the active battler's pending bit and two local-work flag masks, then resets the state bytes. */
MATCH void func_801E1050(void) {
    PartyMember* work;

    Battle_ClearSlotPending(g_Task->slot);
    work = g_Game.current;
    work->u.turn.damage_flags.value =
        work->u.turn.damage_flags.value &
        ~(COMBATANT_FLAG_UNK_4 | COMBATANT_FLAG_UNK_5 | COMBATANT_FLAG_DAMAGED | COMBATANT_FLAG_DAMAGE_NUMBER);
    work->u.turn.damage_flags.value = work->u.turn.damage_flags.value & ~COMBATANT_FLAG_DAMAGE_ROW_PRESENT;
    g_Task->header.mode             = 3;
    g_Task->header.step             = 0;
    g_Task->unk_03                  = 0;
}

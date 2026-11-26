#include "battle_03.h"

/* Clears the active battler's pending bit and two local-work flag masks, then resets the state bytes. */
MATCH void func_801E1050(void) {
    PartyMember* work;

    Battle_ClearSlotPending(SELF(PartyMember)->slot);
    work                            = g_Game.current;
    work->u.turn.damage_flags.value = work->u.turn.damage_flags.value & ~(BATTLER_DAMAGE_UNK_4 | BATTLER_DAMAGE_UNK_5 | BATTLER_DAMAGE_TAKEN | BATTLER_DAMAGE_NUMBER);
    work->u.turn.damage_flags.value = work->u.turn.damage_flags.value & ~BATTLER_DAMAGE_ROW_PRESENT;
    SELF(PartyMember)->header.mode  = 3;
    SELF(PartyMember)->header.step  = 0;
    SELF(PartyMember)->unk_03       = 0;
}

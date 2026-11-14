#include "battle_03.h"

/* counts the work area's step byte down; at expiry it requests the queued battle message, adds the
 * follow-up when the message flag allows it and advances the step byte.
 */
MATCH void func_801E1888(void) {
    PartyMember* work;
    u8           count;

    work  = g_Task;
    count = work->unk_09;
    if (count == 0) {
        func_801DD858(5);
        if ((g_Game.current->u.turn.action_flags.value & COMBATANT_FLAG_DRAGON_FORM) && ((g_Battle.dragon_form & BYTE_MASK) != 4) && ((u32)((short)g_Battle.dragon_form - 7) >= 2)) {
            func_801DD858(3);
        }
        g_Task->header.step = g_Task->header.step + 1;
    } else {
        g_Task->unk_09 = count - 1;
    }
    Battle_IsPartyMemberBlocked();
}

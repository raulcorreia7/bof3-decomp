#include "battle_03.h"

/* counts the work area's step byte down; at expiry it requests the queued battle message, adds the
 * follow-up when the message flag allows it and advances the step byte.
 */
MATCH void func_801E1888(void) {
    PartyMember* work;
    u8           count;

    work  = SELF(PartyMember);
    count = work->unk_09;
    if (count == 0) {
        Battle_PlayEffectSE(5);
        if ((g_Game.current->u.turn.action_flags.value & BATTLER_ACTION_DRAGON_FORM) && ((g_Battle.dragon_form & BYTE_MASK) != 4) && ((u32)((short)g_Battle.dragon_form - 7) >= 2)) {
            Battle_PlayEffectSE(3);
        }
        SELF(PartyMember)->header.step = SELF(PartyMember)->header.step + 1;
    } else {
        SELF(PartyMember)->unk_09 = count - 1;
    }
    Battle_IsPartyMemberBlocked();
}

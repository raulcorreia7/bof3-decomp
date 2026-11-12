#include "battle_15.h"

/* on a 1-in-4 roll sets the panel event flag and kicks off the
 *           effect call for the active pair, storing the returned id;
 *           otherwise marks the panel record and runs the fallback effect
 *           path.
 * FAKE: the volatile halfword load keeps the argument load ahead of it, and the
 * plain store lets the halfword write fill the call delay slot.
 */
MATCH void func_8009EF28(void) {
    u16 flag_value;
    /* FAKE: pin the halfword address to v0. */
    FAKE_REG(volatile u16*, half, "v0");
    BattleTurn* record;
    u16         updated;
    u8          battler_index;
    u8          selection_kind;

    if (RANDOM_MASK(0x7F) < 0x20) {
        battler_index                     = g_BattleActiveBattler;
        half                              = (volatile u16*)&g_Battle.state;
        flag_value                        = *half;
        selection_kind                    = g_Battle.target;
        updated                           = flag_value | BATTLE_STATE_CRITICAL;
        *(u16*)half                       = updated;
        g_Battle.target_record->hp_change = Battle_CalcDamage(battler_index, selection_kind, BATTLE_ELEMENT_FROM_WEAPON);
        return;
    }
    record               = g_Battle.target_record;
    record->target_flags = 1;
    Battle_QueueAction(0, g_Battle.target);
    func_800A3F28();
}

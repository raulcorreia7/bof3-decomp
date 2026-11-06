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
    MATCH_REG(volatile u16*, half, "v0");
    /* FAKE: pin the record base to v1 in the else path. */
    MATCH_REG(BattleTurn*, record, "v1");
    u16 updated;
    u8  battler_index;
    u8  selection_kind;

    if ((RANDOM_MASK(0x7F)) < 0x20) {
        battler_index                   = g_BattleActiveBattler;
        half                            = (volatile u16*)&g_BattleState;
        flag_value                      = *half;
        selection_kind                  = g_BattleTarget;
        updated                         = flag_value | BATTLE_STATE_CRITICAL;
        *(u16*)half                     = updated;
        g_BattleTargetRecord->hp_change = Battle_CalcDamage(battler_index, selection_kind, BATTLE_ELEMENT_FROM_WEAPON);
        return;
    }
    record               = g_BattleTargetRecord;
    record->target_flags = 1;
    func_800AAC88(0, g_BattleTarget);
    func_800A3F28();
}

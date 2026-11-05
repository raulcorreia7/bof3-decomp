#include "battle_15.h"

/* reports whether the selection confirm step may play a random cue:
 * the slot must be free, its panel flag bit 0 set, its id equal to the active
 * selection, and the sub-check must report 0.
 */
MATCH s32 func_800AA7A0(u8 slot) {
    s32 random_range;
    u8  sub;

    if (Battle_SlotIsBlocked(slot) != 0) {
        return 0;
    }
    if ((g_BattlePartyBattlers[slot].flags_124.value & 1) == 0) {
        return 0;
    }
    if (g_BattlePartyBattlers[slot].unk_118 != *(u8*)&g_BattleActiveBattler) {
        return 0;
    }
    sub = func_800AA8A4(slot);
    if (sub == 0) {
        random_range = 2;
        return rand() % random_range == 0;
    }
    return 0;
}

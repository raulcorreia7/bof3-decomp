#include "battle_15.h"

/* Selection record at 0x800B65F8: a u16 id followed by the handler word that
 * D_800B65FC exposes as BattleSelectionAction. */

/* func_800AE1F8 */
MATCH void Battle_LoadSelectionEffect(s32 selection_index) {
    volatile u16* flags;
    u16           value;

    value = g_BattleSelections[g_BattleActionSelection[selection_index & BYTE_MASK]].id;
    if (value != 0xFFFF) {
        EMI_LoaderStreamInitSlot(value);
        BATTLE_RAISE_STATE(BATTLE_STATE_EFFECT_LOADING);
    }
}

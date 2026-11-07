#include "battle_15.h"

/* reports whether the current character may select the kind stored in
 * the active selection-scratch entry.
 */
MATCH s32 func_80097574(void) {
    u8* slot = (u8*)&D_80148656;
    u8* entry;

    entry = Party_GetAbilities(*slot, g_MenuPanelTasks[16].unk_0B, 1);
    return (func_801AF5B0(2, *slot, entry[g_MenuPanelTasks[16].unk_0C]) & BYTE_MASK) == 0;
}

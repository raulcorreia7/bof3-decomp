#include "battle_15.h"

/* reports whether the current character may select the kind stored in
 * the active selection-scratch entry.
 */
MATCH s32 func_80097574(void) {
    u8* slot = (u8*)&D_80148656;
    u8* entry;

    entry = Party_GetAbilities(*slot, D_8014857B, 1);
    return (func_801AF5B0(2, *slot, entry[D_8014857C]) & 0xFF) == 0;
}

#include "battle_15.h"

/* func_800AC754 */
MATCH volatile u8* Battle_FindActorEntry(u8 entry_id) {
    s32 index;
    s32 offset;

    for (index = 0; (u32)(index & BYTE_MASK) < BATTLE_ENTRY_COUNT; index++) {
        offset = (index & BYTE_MASK) * BATTLE_ENTRY_STRIDE;
        if (D_8014688E[offset] == BATTLE_ENTRY_TYPE && D_8014691A[offset] == entry_id) {
            /* FAKE: retail reads g_Actors as volatile u8[]. */
            return ((volatile u8*)g_Actors) + offset;
        }
    }
    return NULL;
}

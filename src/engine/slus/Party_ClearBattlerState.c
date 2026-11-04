#include "engine/slus/slus.h"

/* clears the four flag bytes of the 0x140-stride record selected by character_index.
 */
MATCH void Party_ClearBattlerState(s32 character_index) {
    u32 index;

    index             = (character_index & BYTE_MASK) * 0x140;
    D_80145E91[index] = 0;
    D_80145E92[index] = 0;
    D_80145E93[index] = 0;
    D_80145E94[index] = 0;
}

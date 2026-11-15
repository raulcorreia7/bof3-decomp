#include "game_00.h"

MATCH s32 func_801C69C8(s32 record_index) {
    s32           index;
    FormationPos* slot;
    s32           mode;
    s32           result;
    /* Retail reserves 0x20 variable bytes and never reads them; the unused
     * array reproduces that frame. */
    u8            unk_10[0x20];

    index               = record_index & BYTE_MASK;
    slot                = &g_EncounterParty[index];
    mode                = D_801CD944[index].key;
    result              = 0;
    g_Task->pos.z.fixed = Area_SampleHeight(slot->x.fixed, slot->y.fixed) << 16;
    if ((func_801C7518(slot->x.fixed, slot->y.fixed, mode) & BYTE_MASK) != 0) {
        result = Actor_FindInRange(slot->x.fixed, slot->y.fixed, mode) == -1;
    }
    return result;
}

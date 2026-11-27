#include "area030_04.h"

/* Reports whether the first AREA030 entry is available to the work
 * slot: an entry in state 4 with a blank character index and area state 3
 * returns true when the work page byte is 0x16 and the target matches the entry
 * state, otherwise probes Actor_IsInRange at the work position with the entry's
 * range byte and the entry base; a closed probe steps the work slot and
 * returns false. */
/* func_801E0680 */
MATCH bool Fishing_LureInRange(void) {
    FishingState*  work;
    FishingTarget* target;
    u8             entry_byte;
    s32            range;

    if (g_SpawnedActors[0].header.mode == 4) {
        if (g_FishingHookedFish == GAME_NONE && D_80145E92[0] == 3) {
            if (SELF(FishingState)->cue_index == 0x16 && (g_FishingLureRow->unk_0E & 0xF) == g_SpawnedActors[0].header.mode) {
                return true;
            }
            target     = g_FishingLureRow;
            entry_byte = g_SpawnedActors[0].unk_07;
            /* FAKE: keeps the unk_07 byte load ahead of the scratchpad
             * pointer load (retail +0x8C before +0x90). */
            FAKE_BARRIER();
            work  = SELF(FishingState);
            range = (entry_byte - target->unk_0F + 3) & BYTE_MASK;
            /* FAKE: Actor_IsInRange reads the slot through the field actor layout. */
            if (Actor_IsInRange(work->motion.unk_34, work->y_38.pos_y, work->bounce.half.key, range, (Actor*)g_SpawnedActors) & BYTE_MASK) {
                return true;
            }
        }
    }
    SELF(FishingState)->handler_index = 1;
    return false;
}

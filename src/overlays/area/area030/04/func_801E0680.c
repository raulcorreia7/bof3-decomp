#include "area030_04.h"

/* Reports whether the first AREA030 entry is available to the work
 * slot: an entry in state 4 with a blank character index and area state 3
 * returns true when the work page byte is 0x16 and the row matches the entry
 * state, otherwise probes func_801BDD58 at the work position with the entry's
 * range byte and the entry base; a closed probe steps the work slot and
 * returns false. */
MATCH bool func_801E0680(void) {
    FishingState*  work;
    FishingTarget* row;
    u8             entry_byte;
    s32            range;

    if (g_ActorSlots[0].header.mode == 4) {
        if (D_801E3208 == GAME_NONE && D_80145E92[0] == 3) {
            if (FISHING_STATE->cue_index_06 == 0x16 && (D_801E3210->unk_0E & 0xF) == g_ActorSlots[0].header.mode) {
                return true;
            }
            row        = D_801E3210;
            entry_byte = g_ActorSlots[0].unk_07;
            /* FAKE: keeps the unk_07 byte load ahead of the scratchpad
             * pointer load (retail +0x8C before +0x90). */
            MATCH_BARRIER();
            work  = FISHING_STATE;
            range = (entry_byte - row->unk_0F + 3) & 0xFF;
            /* FAKE: func_801BDD58 reads the slot through the field actor layout. */
            if (func_801BDD58(work->motion_34.unk_34, work->y_38.pos_y, work->bounce_3C.half.key_3E, range,
                              (Actor*)g_ActorSlots) &
                0xFF) {
                return true;
            }
        }
    }
    FISHING_STATE->handler_index_01 = 1;
    return false;
}

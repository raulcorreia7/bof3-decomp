#include "engine/slus/slus.h"

/* publishes a field record's value halfword into the work record's +0x32; the record comes from the helper
 * keyed on byte +0x18 with flag 0x20, otherwise from the scan helper, which reports -1 for none and leaves the field
 * untouched.
 */
/* FAKE: retail reads the key as the low byte (lbu) of the word member. */
MATCH void Actor_ReadValue(void) {
    s8 index;

    if ((SELF(Actor)->active_flags & 0x20) != 0) {
        index               = Script_FindSlot(*(u8*)&SELF(Actor)->unk_18);
        SELF(Actor)->unk_32 = g_Actors[index].unk_32;
    } else {
        index = func_8014DE78();
        if (index != -1) {
            SELF(Actor)->unk_32 = g_Actors[index].unk_32;
        }
    }
}

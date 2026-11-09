#include "engine/slus/slus.h"

/* publishes a field record's value halfword into the record's +0x32. */
/* FAKE: retail reads the key as the low byte (lbu) of the word member. */
MATCH void Actor_ReadValue(void) {
    s8 index;

    if ((g_Task->active_flags & 0x20) != 0) {
        index          = Actor_FindScriptSlot(*(u8*)&g_Task->unk_18);
        g_Task->unk_32 = g_Actors[index].unk_32;
    } else {
        index = func_8014DE78();
        if (index != -1) {
            g_Task->unk_32 = g_Actors[index].unk_32;
        }
    }
}

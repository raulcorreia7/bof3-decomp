#include "area030_04.h"

/* Resets the seven AREA030 object records, re-arms the object slots
 * 7..19, and sets the work-object mode byte to 2. */
MATCH void func_801E0A30(void) {
    s32 i;

    for (i = 0; i < 7; i++) {
        g_ActorSlots[i].header.mode = 0;
        g_ActorSlots[i].header.step = 0;
        g_ActorSlots[i].unk_03      = 0;
        g_ActorSlots[i].unk_04      = 0;
    }
    for (i = 7; i < 20; i++) {
        Actor_Free(i & 0xFF);
    }
    D_8014403D = 2;
}

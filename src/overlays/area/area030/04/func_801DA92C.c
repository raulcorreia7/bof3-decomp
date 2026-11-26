#include "area030_04.h"

/* Advances the AREA030 progress counters and clears the four settle
 * flags before arming the area load step and stepping the work state. */
MATCH void func_801DA92C(void) {
    u8*           counter;
    u8*           flags;
    FishingState* state;
    FishingState* work;
    FishingState* tail;
    s32           i;

    i     = 3;
    flags = &D_801E31E3;

    counter                   = &g_SpawnedActors[1].header.step;
    g_SpawnedActors[4].unk_06 = 1;
    (*counter)++;
    g_SpawnedActors[4].header.mode++;
    SELF(FishingState)->cue_index = 1;

    do {
        *flags = 0;
        i--;
        flags--;
    } while (i >= 0);

    state             = SELF(FishingState);
    state->counter_07 = 0;

    work              = SELF(FishingState);
    work->saved_index = 0;
    Script_Request(3);

    tail            = SELF(FishingState);
    tail->sub_index = (tail->sub_index + 1);
}

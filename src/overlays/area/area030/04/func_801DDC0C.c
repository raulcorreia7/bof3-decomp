#include "area030_04.h"

/* When flag `D_80144125` is clear, calls `UI_ModeSet` with 0 and
 * increments byte 0x03 of the scratchpad work object. */
MATCH void func_801DDC0C(void) {
    if (g_SpawnedActors[3].header.mode == 0) {
        UI_ModeSet(0);
        SELF(Actor)->unk_03 += 1;
    }
}

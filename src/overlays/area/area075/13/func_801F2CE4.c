#include "area075_13.h"

MATCH s32 func_801F2CE4(void) {
    D_801F58CE[TASK(Actor)->param.unk_0B] = TASK(SpawnedActor) - g_SpawnedActors;
    TASK(Actor)->unk_0A                   = 0x80;
    TASK(Actor)->vx                       = 0;
    TASK(Actor)->unk_06                   = 0x1E;
    TASK(Actor)->tint.steps.delta.r       = -0x80;
    TASK(Actor)->header.mode += 1;
}

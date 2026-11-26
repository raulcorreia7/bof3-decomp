#include "area075_13.h"

MATCH s32 func_801F2CE4(void) {
    D_801F58CE[SELF(Actor)->param.unk_0B] = SELF(SpawnedActor) - g_SpawnedActors;
    SELF(Actor)->unk_0A                   = 0x80;
    SELF(Actor)->vx                       = 0;
    SELF(Actor)->unk_06                   = 0x1E;
    SELF(Actor)->tint.steps.delta.r       = -0x80;
    SELF(Actor)->header.mode += 1;
}

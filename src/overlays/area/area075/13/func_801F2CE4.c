#include "area075_13.h"

MATCH s32 func_801F2CE4(void) {
    D_801F58CE[g_Task->param.unk_0B] = TASK(SpawnedActor) - g_SpawnedActors;
    g_Task->unk_0A                   = 0x80;
    g_Task->vx                       = 0;
    g_Task->unk_06                   = 0x1E;
    g_Task->tint.steps.delta.r       = -0x80;
    g_Task->header.mode += 1;
}

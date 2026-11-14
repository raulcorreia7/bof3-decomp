#include "area174_13.h"

MATCH void func_801F3F4C(void) {
    g_SpawnedActors[g_Task->param.actor_slot].header.mode  = 3;
    g_SpawnedActors[g_Task->param.actor_slot].pad_4B[0x12] = 0x70;
    g_SpawnedActors[g_Task->param.actor_slot].pad_4B[0x13] = 0x30;
}

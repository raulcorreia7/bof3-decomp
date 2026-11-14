#include "area171_13.h"

MATCH void func_801F3650(void) {
    s32 index;

    index = func_8019601C() & 0xFF;
    if (index != 0xFF) {
        g_SpawnedActors[index].header.flags = 1;
        g_SpawnedActors[index].type         = 0x92;
        g_SpawnedActors[index].unk_30       = -30;
        g_SpawnedActors[index].unk_29       = 6;
        g_SpawnedActors[index].unk_2E       = 0;
        g_SpawnedActors[index].link         = g_CurrentActor - g_Actors;
    }
    func_801A4BC0(2, 0x21, 0x89);
    func_801A4BC0(2, 0x22, 0x89);
    func_801A4BC0(3, 0x21, 0x89);
    func_801A4BC0(3, 0x22, 0x89);
}

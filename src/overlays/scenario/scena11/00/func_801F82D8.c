#include "scena11_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F82D8(s32 slot) {
    Actor* work;
    Actor* other;

    TASK_SET(&g_SpawnedActors[slot & BYTE_MASK]);
    Area_SceneSelectRecord(0x18);

    g_Task->active_flags = 0;
    g_Task->mirror       = 0;
    g_Task->unk_2B       = (g_Task->unk_2B + 1);
    g_Task->unk_48       = 0;

    work                    = g_Task;
    work->tint.bytes.rgb.r  = 0;
    other                   = g_Task;
    work->vz                = 0;
    work->gravity           = -8;
    other->tint.bytes.rgb.g = 0;

    g_Task->tint.bytes.rgb.b = 0;
    Script_Select(0xE);

    g_Task->header.mode = 3;
    g_Task->header.step = 1;
}

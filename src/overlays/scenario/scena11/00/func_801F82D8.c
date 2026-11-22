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

    TASK(Actor)->active_flags = 0;
    TASK(Actor)->mirror       = 0;
    TASK(Actor)->unk_2B       = (TASK(Actor)->unk_2B + 1);
    TASK(Actor)->unk_48       = 0;

    work                    = TASK(Actor);
    work->tint.bytes.rgb.r  = 0;
    other                   = TASK(Actor);
    work->vz                = 0;
    work->gravity           = -8;
    other->tint.bytes.rgb.g = 0;

    TASK(Actor)->tint.bytes.rgb.b = 0;
    Script_Select(0xE);

    TASK(Actor)->header.mode = 3;
    TASK(Actor)->header.step = 1;
}

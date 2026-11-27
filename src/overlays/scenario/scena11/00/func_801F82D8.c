#include "scena11_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F82D8(s32 slot) {
    Actor* work;
    Actor* other;

    SELF_SET(&g_SpawnedActors[slot & BYTE_MASK]);
    Area_SceneSelectRecord(0x18);

    SELF(Actor)->active_flags = 0;
    SELF(Actor)->mirror       = 0;
    SELF(Actor)->unk_2B       = (SELF(Actor)->unk_2B + 1);
    SELF(Actor)->unk_48       = 0;

    work                    = SELF(Actor);
    work->tint.bytes.rgb.r  = 0;
    other                   = SELF(Actor);
    work->vz                = 0;
    work->gravity           = -8;
    other->tint.bytes.rgb.g = 0;

    SELF(Actor)->tint.bytes.rgb.b = 0;
    Script_Select(0xE);

    SELF(Actor)->header.mode = 3;
    SELF(Actor)->header.step = 1;
}

#include "game_00.h"

MATCH void func_8019E7C4(void) {
    Actor* work;
    Actor* other;

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
    Script_Select(9);

    TASK(Actor)->header.step = (TASK(Actor)->header.step + 1);
}

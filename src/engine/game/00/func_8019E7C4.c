#include "game_00.h"

MATCH void func_8019E7C4(void) {
    Actor* work;
    Actor* other;

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
    Script_Select(9);

    SELF(Actor)->header.step = (SELF(Actor)->header.step + 1);
}

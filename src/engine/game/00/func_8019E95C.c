#include "game_00.h"

MATCH void func_8019E95C(void) {
    Actor* work;
    Actor* other;

    if ((u8)Area_SceneSelectRecord(0x46) != 0) {
        Actor_Clear();
        return;
    }

    SELF(Actor)->draw_layer   = (SELF(Actor)->draw_layer + 1);
    SELF(Actor)->mirror       = 0;
    SELF(Actor)->active_flags = 0;
    SELF(Actor)->unk_2B       = (SELF(Actor)->unk_2B + 1);
    SELF(Actor)->unk_48       = 1;

    work                          = SELF(Actor);
    work->tint.bytes.rgb.r        = 0;
    other                         = SELF(Actor);
    work->vy                      = -0x2000;
    work->vx                      = 0;
    work->vz                      = 64;
    other->tint.bytes.rgb.g       = 0;
    SELF(Actor)->tint.bytes.rgb.b = 0;
    Script_Select(0);
    SELF(Actor)->header.step = (SELF(Actor)->header.step + 1);
}

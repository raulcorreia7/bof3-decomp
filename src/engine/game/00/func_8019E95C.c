#include "game_00.h"

MATCH void func_8019E95C(void) {
    Actor* work;
    Actor* other;

    if ((u8)Area_SceneSelectRecord(0x46) != 0) {
        Actor_Clear();
        return;
    }

    TASK(Actor)->draw_layer   = (TASK(Actor)->draw_layer + 1);
    TASK(Actor)->mirror       = 0;
    TASK(Actor)->active_flags = 0;
    TASK(Actor)->unk_2B       = (TASK(Actor)->unk_2B + 1);
    TASK(Actor)->unk_48       = 1;

    work                          = TASK(Actor);
    work->tint.bytes.rgb.r        = 0;
    other                         = TASK(Actor);
    work->vy                      = -0x2000;
    work->vx                      = 0;
    work->vz                      = 64;
    other->tint.bytes.rgb.g       = 0;
    TASK(Actor)->tint.bytes.rgb.b = 0;
    Script_Select(0);
    TASK(Actor)->header.step = (TASK(Actor)->header.step + 1);
}

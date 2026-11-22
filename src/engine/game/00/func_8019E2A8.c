#include "game_00.h"

MATCH void func_8019E2A8(void) {
    Actor* work;
    Actor* state;
    Actor* other;
    Actor* flags;

    Area_SceneSelectRecord(0x18);
    TASK(Actor)->active_flags       = 0;
    TASK(Actor)->mirror             = 0;
    work                            = TASK(Actor);
    work->unk_2B                    = (work->unk_2B + 1);
    TASK(Actor)->unk_48             = 0;
    state                           = TASK(Actor);
    state->tint.steps.delta.r       = 0;
    other                           = TASK(Actor);
    state->vz                       = 64;
    state->gravity                  = -8;
    other->tint.steps.delta.g       = 0;
    TASK(Actor)->tint.steps.delta.b = 0;
    Script_Select(8);
    flags              = TASK(Actor);
    flags->header.step = (flags->header.step + 1);
}

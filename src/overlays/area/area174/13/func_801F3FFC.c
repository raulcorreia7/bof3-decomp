#include "area174_13.h"

MATCH void func_801F3FFC(void) {
    s8     tint_a;
    s8     tint_b;
    s8     tint_c;
    Actor* work;
    Actor* scratch;

    work = SELF(Actor);
    COORD_INT(work->pos.z) -= 0x14;
    tint_a = work->tint.steps.delta.r;
    if (tint_a < -0x40) {
        work->tint.steps.delta.r = tint_a + 2;
    }
    scratch = SELF(Actor);
    tint_b  = scratch->tint.steps.delta.g;
    if (tint_b < -0x40) {
        scratch->tint.steps.delta.g = tint_b + 2;
        scratch                     = SELF(Actor);
    }
    tint_c = scratch->tint.steps.delta.b;
    if (tint_c < -0x40) {
        scratch->tint.steps.delta.b = tint_c + 2;
    }
    if (COORD_INT(SELF(Actor)->pos.z) == 0xA00) {
        SELF(Actor)->header.flags &= ~0x20;
        SELF(Actor)->tint.bytes.flags = 0;
        {
            Actor* task            = SELF(Actor);
            task->tint.bytes.rgb.b = 0;
            task->tint.bytes.rgb.g = 0;
            task->tint.bytes.rgb.r = 0;
        }
    } else {
        g_CurrentActor->unk_7E -= 2;
    }
}

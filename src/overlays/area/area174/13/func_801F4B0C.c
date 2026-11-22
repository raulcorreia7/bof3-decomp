#include "area174_13.h"

MATCH void func_801F4B0C(void) {
    Actor* work;

    TASK(Actor)->pos.z.part.integer += 8;
    if (g_PaletteFades[g_CurrentActor->unk_93].offset.r < 30) {
        g_PaletteFades[g_CurrentActor->unk_93].offset.r += 2;
        g_PaletteFades[g_CurrentActor->unk_93].offset.g += 2;
        g_PaletteFades[g_CurrentActor->unk_93].offset.b += 2;
    } else {
        TASK(Actor)->header.flags |= 0x20;
        TASK(Actor)->tint.bytes.flags = 1;
        work                          = TASK(Actor);
        work->tint.steps.delta.r = work->tint.steps.delta.g = work->tint.steps.delta.b = -0x40;
        TASK(Actor)->unk_04                                                            = 1;
    }
    g_ScriptState->cursor -= 2;
}

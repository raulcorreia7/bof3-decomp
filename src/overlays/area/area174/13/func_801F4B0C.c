#include "area174_13.h"

MATCH void func_801F4B0C(void) {
    Actor* work;

    g_Task->pos.z.part.integer += 8;
    if (g_PaletteFades[g_CurrentActor->unk_93].offset.r < 30) {
        g_PaletteFades[g_CurrentActor->unk_93].offset.r += 2;
        g_PaletteFades[g_CurrentActor->unk_93].offset.g += 2;
        g_PaletteFades[g_CurrentActor->unk_93].offset.b += 2;
    } else {
        g_Task->header.flags |= 0x20;
        g_Task->tint.bytes.flags        = 1;
        work                            = g_Task;
        work->tint.signed_bytes.delta.r = work->tint.signed_bytes.delta.g = work->tint.signed_bytes.delta.b = -0x40;
        g_Task->unk_04                                                                                      = 1;
    }
    g_ScriptState->cursor -= 2;
}

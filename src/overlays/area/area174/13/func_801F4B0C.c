#include "area174_13.h"

MATCH void func_801F4B0C(void) {
    Actor* work;

    g_Task->pos.z.part.integer += 8;
    if (g_PaletteFades[g_CurrentActor->unk_93].offset.red < 30) {
        g_PaletteFades[g_CurrentActor->unk_93].offset.red += 2;
        g_PaletteFades[g_CurrentActor->unk_93].offset.green += 2;
        g_PaletteFades[g_CurrentActor->unk_93].offset.blue += 2;
    } else {
        g_Task->header.flags |= 0x20;
        g_Task->tint.bytes.flags          = 1;
        work                              = g_Task;
        work->tint.signed_bytes.delta.red = work->tint.signed_bytes.delta.green = work->tint.signed_bytes.delta.blue = -0x40;
        g_Task->unk_04                                                                                               = 1;
    }
    g_ScriptState->cursor -= 2;
}

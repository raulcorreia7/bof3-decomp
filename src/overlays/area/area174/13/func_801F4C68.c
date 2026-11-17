#include "area174_13.h"

MATCH void func_801F4C68(void) {
    Actor* work;
    s8     shade;

    work = g_Task;
    work->pos.z.part.integer += 8;
    shade = work->tint.steps.delta.r;
    if (shade != -0x80) {
        work->tint.steps.delta.r = shade - 4;
        g_Task->tint.bytes.rgb.g -= 4;
        g_Task->tint.bytes.rgb.b -= 4;
        g_ScriptState->cursor -= 2;
    } else {
        work->header.flags |= 0x40;
        g_Task->unk_04 = 0;
    }
}

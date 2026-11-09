#include "area172_13.h"

MATCH void func_801F440C(void) {
    Actor* work;

    g_Task->header.flags &= ~0x40;
    g_Task->header.flags |= 0x20;
    g_Task->tint.bytes.flags         = 1;
    g_Task->tint.signed_bytes.unk_5D = -0x80;
    g_Task->tint.signed_bytes.unk_5E = -0x80;
    g_Task->tint.signed_bytes.unk_5F = -0x80;
    work                             = g_Task;
    work->unk_04                     = 1;
    work->vx                         = 0;
    work->vy                         = 0;
    work->vz                         = 0;
    work->gravity                    = -8;
    g_ScriptState->cursor -= 2;
}

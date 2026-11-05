#include "area075_13.h"

MATCH void func_801F346C(void) {
    s8 blue;

    blue = g_Task->tint.signed_bytes.unk_5D;
    if (blue != -0x80) {
        g_Task->tint.bytes.unk_5D = blue - 8;
        g_Task->tint.bytes.unk_5E -= 8;
        g_Task->tint.bytes.unk_5F -= 8;
        g_Task->x.fixed += g_Task->vx;
        g_Task->y.fixed += g_Task->vy;
        g_Task->z.part.integer += g_Task->vz;
        g_ScriptState->cursor -= 2;
    } else {
        g_Task->flags = 0;
    }
}

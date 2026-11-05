#include "area075_13.h"

MATCH void func_801F346C(void) {
    s8 blue;

    blue = g_SpadWork->tint.signed_bytes.unk_5D;
    if (blue != -0x80) {
        g_SpadWork->tint.bytes.unk_5D = blue - 8;
        g_SpadWork->tint.bytes.unk_5E -= 8;
        g_SpadWork->tint.bytes.unk_5F -= 8;
        g_SpadWork->x.fixed += g_SpadWork->vx;
        g_SpadWork->y.fixed += g_SpadWork->vy;
        g_SpadWork->z.part.integer += g_SpadWork->vz;
        g_ScriptState->cursor -= 2;
    } else {
        g_SpadWork->flags_00 = 0;
    }
}

#include "area141_13.h"

MATCH void func_801F390C(void) {
    s8     tintA;
    s8     tintB;
    s8     tintC;
    Actor* spad;
    Actor* spad2;

    spad = g_Task;
    spad->pos.x.fixed += spad->vx;
    spad->pos.y.fixed += spad->vy;
    tintA = spad->tint.signed_bytes.delta.red;
    if (tintA < -0x40) {
        spad->tint.signed_bytes.delta.red = tintA + 4;
    }
    spad2 = g_Task;
    tintB = spad2->tint.signed_bytes.delta.green;
    if (tintB < -0x40) {
        spad2->tint.signed_bytes.delta.green = tintB + 4;
        spad2                                = g_Task;
    }
    tintC = spad2->tint.signed_bytes.delta.blue;
    if (tintC < -0x40) {
        spad2->tint.signed_bytes.delta.blue = tintC + 4;
    }
    if ((g_Task->tint.word & 0xFFFFFF00) == 0xC0C0C000) {
        g_Task->header.flags &= ~0x20;
        g_Task->tint.bytes.flags = 0;
        {
            Actor* spad                = g_Task;
            spad->tint.bytes.rgb.blue  = 0;
            spad->tint.bytes.rgb.green = 0;
            spad->tint.bytes.rgb.red   = 0;
        }
        g_Task->unk_04 = 0;
    } else {
        g_CurrentActor->unk_7E -= 2;
    }
}

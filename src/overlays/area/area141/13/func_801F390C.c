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
    tintA = spad->tint.signed_bytes.unk_5D;
    if (tintA < -0x40) {
        spad->tint.signed_bytes.unk_5D = tintA + 4;
    }
    spad2 = g_Task;
    tintB = spad2->tint.signed_bytes.unk_5E;
    if (tintB < -0x40) {
        spad2->tint.signed_bytes.unk_5E = tintB + 4;
        spad2                           = g_Task;
    }
    tintC = spad2->tint.signed_bytes.unk_5F;
    if (tintC < -0x40) {
        spad2->tint.signed_bytes.unk_5F = tintC + 4;
    }
    if ((g_Task->tint.word & 0xFFFFFF00) == 0xC0C0C000) {
        g_Task->header.flags &= ~0x20;
        g_Task->tint.bytes.flags = 0;
        {
            Actor* spad             = g_Task;
            spad->tint.bytes.unk_5F = 0;
            spad->tint.bytes.unk_5E = 0;
            spad->tint.bytes.unk_5D = 0;
        }
        g_Task->unk_04 = 0;
    } else {
        g_CurrentActor->unk_7E -= 2;
    }
}

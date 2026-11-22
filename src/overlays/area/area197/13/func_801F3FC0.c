#include "area197_13.h"

MATCH void func_801F3FC0(void) {
    if (TASK(Actor)->unk_0A != 0) {
        TASK(Actor)->pos.x.fixed += D_801F4A88[TASK(Actor)->unk_0A & 0xF] << 11;
        TASK(Actor)->pos.y.fixed -= D_801F4A88[TASK(Actor)->unk_0A & 0xF] << 11;
        TASK(Actor)->unk_0A -= 1;
        g_CurrentActor->unk_7E -= 2;
    } else {
        TASK(Actor)->unk_04 = 0;
    }
}

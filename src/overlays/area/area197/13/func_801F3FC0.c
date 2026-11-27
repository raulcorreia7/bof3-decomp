#include "area197_13.h"

MATCH void func_801F3FC0(void) {
    if (SELF(Actor)->unk_0A != 0) {
        SELF(Actor)->pos.x.fixed += D_801F4A88[SELF(Actor)->unk_0A & 0xF] << 11;
        SELF(Actor)->pos.y.fixed -= D_801F4A88[SELF(Actor)->unk_0A & 0xF] << 11;
        SELF(Actor)->unk_0A -= 1;
        g_CurrentActor->unk_7E -= 2;
    } else {
        SELF(Actor)->unk_04 = 0;
    }
}

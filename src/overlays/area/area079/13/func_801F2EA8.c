#include "area079_13.h"

MATCH void func_801F2EA8(void) {
    Actor* work;

    work = (Actor*)g_Task;
    if (work->unk_0A != 0) {
        work->x.fixed += D_801F4C84[work->unk_0A & 0xF] << 11;
        work->y.fixed -= D_801F4C84[work->unk_0A & 0xF] << 11;
        work->unk_0A -= 1;
        g_GameState->unk_122 -= 2;
    } else {
        ((u8*)work)[0x04] = 0;
    }
}

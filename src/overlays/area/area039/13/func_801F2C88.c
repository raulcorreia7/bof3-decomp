#include "area039_13.h"

MATCH void func_801F2C88(void) {
    Actor* work;

    work = (Actor*)g_Task;
    if (work->unk_0A != 0) {
        work->pos.x.fixed += ((s8*)(D_801F4C10 + 8))[work->unk_0A & 0xF] << 11;
        work->pos.y.fixed -= ((s8*)(D_801F4C10 + 8))[work->unk_0A & 0xF] << 11;
        work->unk_0A -= 1;
        FIELD(u16, g_CurrentActor, 0x7Eu) -= 2;
    } else {
        ((u8*)work)[0x04] = 0;
    }
}

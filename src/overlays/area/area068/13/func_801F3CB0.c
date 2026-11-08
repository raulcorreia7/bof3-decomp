#include "area068_13.h"

MATCH void func_801F3CB0(void) {
    Actor* work;

    work = g_Task;
    if (work->unk_0A != 0) {
        work->pos.x.fixed += ((s8*)(D_801F4DE4 + 8))[work->unk_0A & 0xF] << 11;
        work->pos.y.fixed -= ((s8*)(D_801F4DE4 + 8))[work->unk_0A & 0xF] << 11;
        work->unk_0A -= 1;
        g_GameState->u.field.unk_122 -= 2;
    } else {
        work->unk_04 = 0;
    }
}

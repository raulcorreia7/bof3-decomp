#include "game_00.h"

MATCH void func_8019A848(void) {
    Actor* work;

    D_801C80C8[g_SpadWork->unk_06]();

    work = g_SpadWork;
    work->unk_2E += work->vx;
    work->unk_30 -= work->vy;
}

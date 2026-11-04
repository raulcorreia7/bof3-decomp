#include "area172_13.h"

MATCH void func_801F33F0(void) {
    Actor* work;
    Actor* step;

    work         = g_SpadWork;
    work->unk_09 = 0x20;
    step         = g_SpadWork;
    work->unk_0C = 0;
    step->unk_01++;
    g_AreaDrawFlags = 0;
}

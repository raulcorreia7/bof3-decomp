#include "area172_13.h"

MATCH void func_801F33F0(void) {
    Actor* work;
    Actor* step;

    work         = g_Task;
    work->unk_09 = 0x20;
    step         = g_Task;
    work->vx     = 0;
    step->header.mode++;
    g_AreaDrawFlags = 0;
}

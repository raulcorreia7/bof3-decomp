#include "area157_13.h"

MATCH void func_801F3718(void) {
    Actor* work;

    work = g_SpadWork;
    work->unk_30 += 0x20;
    if (work->unk_30 >= 0x100) {
        work->state_02++;
    }
}

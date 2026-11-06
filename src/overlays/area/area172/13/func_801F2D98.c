#include "area172_13.h"

MATCH void func_801F2D98(void) {
    PartyBattler* work;

    work         = g_Task;
    work->unk_09 = work->unk_09 - 1;
    if (g_Task->unk_09 == 0) {
        Actor_Clear();
    }
    func_801F2DF4(1);
}

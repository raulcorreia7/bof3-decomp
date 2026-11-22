#include "area172_13.h"

MATCH void func_801F2D98(void) {
    PartyMember* work;

    work         = TASK(Actor);
    work->unk_09 = work->unk_09 - 1;
    if (TASK(Actor)->timer == 0) {
        Actor_Clear();
    }
    func_801F2DF4(1);
}

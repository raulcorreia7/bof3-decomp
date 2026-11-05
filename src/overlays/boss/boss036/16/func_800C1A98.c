#include "boss036_16.h"

MATCH void func_800C1A98(void) {
    Actor* work = (Actor*)g_SpadWork;

    work->x.fixed = work->x.fixed - work->vx;
    if (work->x.fixed == work->unk_18) {
        work->state_02++;
    }
    func_801E30F8();
}

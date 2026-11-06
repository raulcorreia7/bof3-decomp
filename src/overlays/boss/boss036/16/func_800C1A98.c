#include "boss036_16.h"

MATCH void func_800C1A98(void) {
    Actor* work = (Actor*)g_Task;

    work->pos.x.fixed -= work->vx;
    if (work->pos.x.fixed == work->unk_18) {
        work->header.step++;
    }
    func_801E30F8();
}

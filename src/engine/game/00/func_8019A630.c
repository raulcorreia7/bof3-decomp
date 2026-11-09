#include "game_00.h"

MATCH void func_8019A630(void) {
    Actor* work;
    Actor* next;

    if (Actor_StepAnimOnce() != 0u) {
        work = g_Task;
        work->header.mode++;
    }

    next = g_Task;
    if (next->unk_05 == 6) {
        Area_AddActor();
        return;
    }
    func_8014D290();
}

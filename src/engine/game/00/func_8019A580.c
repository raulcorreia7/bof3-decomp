#include "game_00.h"

MATCH void func_8019A580(void) {
    Actor* work;
    Actor* next;

    work = g_Task;
    work->timer--;
    next = g_Task;
    if (next->timer == 0) {
        next->header.mode++;
        return;
    }
    Actor_StepAnimLoop();
    next = g_Task;
    if ((next->timer & 0x4) != 0) {
        if (next->unk_05 == 6) {
            Area_AddActor();
            return;
        }
        func_8014D290();
    }
}

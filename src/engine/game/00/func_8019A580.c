#include "game_00.h"

MATCH void func_8019A580(void) {
    Actor* work;
    Actor* next;

    work = g_Task;
    work->unk_09--;
    next = g_Task;
    if (next->unk_09 == 0) {
        next->header.mode++;
        return;
    }
    func_8014D978();
    next = g_Task;
    if ((next->unk_09 & 4) != 0) {
        if (next->unk_05 == 6) {
            Area_AddActor();
            return;
        }
        func_8014D290();
    }
}

#include "game_00.h"

MATCH void func_8019A6AC(void) {
    Actor* work;

    g_Task->unk_09--;
    if (g_Task->unk_09 == 0) {
        g_Task->header.mode++;
        return;
    }
    g_Task->tint.bytes.unk_5D -= 6;
    g_Task->tint.bytes.unk_5E -= 6;
    g_Task->tint.bytes.unk_5F -= 6;
    func_8014D978();
    work = g_Task;
    if (work->unk_05 == 6) {
        if ((work->unk_09 & 1) != 0) {
            work->unk_30++;
        }
        Area_AddActor();
    } else {
        if ((work->unk_09 & 1) != 0) {
            work->vy--;
        }
        func_8014D290();
    }
}

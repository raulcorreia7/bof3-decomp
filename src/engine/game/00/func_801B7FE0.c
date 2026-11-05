#include "game_00.h"

MATCH void func_801B7FE0(void) {
    Actor* work;
    Actor* store;
    s16    value;
    u8     arg;

    work = g_Task;
    work->z.part.integer -= 0x10;
    if (work->z.part.integer < Area_ReadHeight(work->x.fixed, work->y.fixed)) {
        value                 = Area_ReadHeight(g_Task->x.fixed, g_Task->y.fixed);
        store                 = g_Task;
        store->unk_09         = 2;
        store->z.part.integer = value;
        g_Task->unk_0A        = 0;
        Actor_RequestScript((g_Task->direction_08 == 3) ? 7 : 1);
        g_Task->unk_04 = 9;
    }
    func_8014D978();
}

#include "area173_14.h"

MATCH void func_801F3DC0(void) {
    Actor* work;
    u16    screen_y;

    work           = g_Task;
    screen_y       = work->screen_y + 0x10;
    work->screen_y = screen_y;
    if ((s16)screen_y >= 0xC0) {
        g_Task->header.step += 1;
    }
    func_801F3FBC(0, (s16)g_Task->screen_y >= 0x80 ? -2 : -1);
    func_801F3FBC(1, 1);
}

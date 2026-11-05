#include "area173_14.h"

MATCH void func_801F3DC0(void) {
    Actor* work;
    u16    screen_y;

    work         = g_SpadWork;
    screen_y     = work->unk_30 + 0x10;
    work->unk_30 = screen_y;
    if ((s16)screen_y >= 0xC0) {
        g_SpadWork->state_02 += 1;
    }
    func_801F3FBC(0, (s16)g_SpadWork->unk_30 >= 0x80 ? -2 : -1);
    func_801F3FBC(1, 1);
}

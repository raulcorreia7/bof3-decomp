#include "area172_13.h"

MATCH void func_801F4DE0(void) {
    Actor* work;
    u16    screen_x;
    u8*    counter;

    work         = g_SpadWork;
    screen_x     = work->unk_2E + 0xA;
    work->unk_2E = screen_x;
    if ((s16)screen_x >= 0x191) {
        counter = &D_80146875;
        *counter += 1;
        work->unk_01 = 2;
    }
    func_801F4E8C(0xDC, 0xC8);
    func_801F4F70((s16)g_SpadWork->unk_2E, 0xC8);
}

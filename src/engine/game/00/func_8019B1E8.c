#include "game_00.h"

MATCH void func_8019B1E8(void) {
    Actor* work;
    s32    count;
    u8     flag;

    if (func_8014DAEC() & BYTE_MASK) {
        count              = g_SpadWork->unk_09 - 1;
        g_SpadWork->unk_09 = (u8)count;
        if ((count & BYTE_MASK) == 0) {
            g_SpadWork->unk_01 = 2;
        }
    }
    work = g_SpadWork;
    flag = work->option_flags;
    if ((flag != 0) && (flag == FIELD(u8, work, 0x58u))) {
        work->unk_01 = 2;
    }
    func_8014D290();
}

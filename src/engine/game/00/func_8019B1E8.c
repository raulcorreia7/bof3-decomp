#include "game_00.h"

MATCH void func_8019B1E8(void) {
    Actor* work;
    s32    count;
    u8     flag;

    if (func_8014DAEC() & BYTE_MASK) {
        count          = g_Task->unk_09 - 1;
        g_Task->unk_09 = count;
        if ((count & BYTE_MASK) == 0) {
            g_Task->header.mode = 2;
        }
    }
    work = g_Task;
    flag = work->option_flags;
    if ((flag != 0) && (flag == FIELD(u8, work, 0x58u))) {
        work->header.mode = 2;
    }
    func_8014D290();
}

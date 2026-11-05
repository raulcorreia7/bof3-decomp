#include "area143_13.h"

MATCH void func_801F3F94(void) {
    Actor* work;
    u32    pos[3];

    work   = g_Task;
    pos[0] = FIELD(u32, work, 0x34);
    pos[1] = FIELD(u32, work, 0x38);
    pos[2] = FIELD(u32, work, 0x3C);
    func_801F3FDC(pos);
}

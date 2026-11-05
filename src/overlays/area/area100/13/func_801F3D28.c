#include "area100_13.h"

MATCH void func_801F3D28(void) {
    s32 pos[3];
    u8* work = TASK_BYTES;

    pos[0] = FIELD(s32, work, 0x34);
    pos[1] = FIELD(s32, work, 0x38);
    pos[2] = FIELD(s32, work, 0x3C);
    func_801F3D70(pos);
}

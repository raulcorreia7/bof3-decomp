#include "area047_13.h"

MATCH void func_801F3448(void) {
    u8* sp;

    sp = TASK_BYTES;
    if (sp[0x2] == 0) {
        FIELD(s32, sp, 0x34) = -0x3900;
        FIELD(s32, sp, 0x38) = -0x3880;
        FIELD(s32, sp, 0x3C) = -0x7F0;
        sp[0x2] += 1;
    }
    func_801F34A0();
}

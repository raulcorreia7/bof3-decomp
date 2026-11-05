#include "area170_13.h"

MATCH void func_801F3F84(void) {
    u8* work;

    work = SP_REF(u8*, 0x44);
    if (FIELD(u8, work, 0x08) != 0) {
        if (abs(D_80145EC8 - ((((s32)FIELD(s16, work, 0x3A) + 1) << 16) | 0x8000)) > 0x20000) {
            goto advance;
        }
        if (abs(D_80145EC4 - ((s32)FIELD(s16, work, 0x36) << 16)) <= 0x20000) {
            return;
        }
        if (abs(D_80145EC4 - (((s32)FIELD(s16, work, 0x36) + 1) << 16)) <= 0x20000) {
            return;
        }
    } else {
        if (abs(D_80145EC4 - ((((s32)FIELD(s16, work, 0x36) + 1) << 16) | 0x8000)) > 0x20000) {
            goto advance;
        }
        if (abs(D_80145EC8 - ((s32)FIELD(s16, work, 0x3A) << 16)) <= 0x20000) {
            return;
        }
        if (abs(D_80145EC8 - (((s32)FIELD(s16, work, 0x3A) + 1) << 16)) <= 0x20000) {
            return;
        }
    }
advance:
    FIELD(u8, work, 0x02)++;
}

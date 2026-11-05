#include "area148_13.h"

MATCH void func_801F3720(void) {
    u8* work;

    work                   = TASK_BYTES;
    FIELD(u16, work, 0x30) = (FIELD(u16, work, 0x30) + 8);
    if ((s16)FIELD(u16, work, 0x30) >= 0x80) {
        work[2]++;
    }
    func_801F37B8(0, -1);
    func_801F37B8(1, 1);
}

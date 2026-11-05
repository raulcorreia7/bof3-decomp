#include "area140_13.h"

MATCH void func_801F2E64(void) {
    u8* work;

    work                   = (u8*)g_Task;
    FIELD(u16, work, 0x30) = (FIELD(u16, work, 0x30) - 0x20);
    if ((s16)FIELD(u16, work, 0x30) < -0xFF) {
        work[2]++;
    }
    func_801F3050();
}

#include "area117_13.h"

MATCH void func_801F2F00(void) {
    u8* work;

    work                    = (u8*)g_Task;
    FIELD(u16, work, 0x30u) = (FIELD(u16, work, 0x30u) - 0x20);
    if ((s16)FIELD(u16, work, 0x30u) < -0xFF) {
        work[2]++;
    }
    func_801F314C();
}

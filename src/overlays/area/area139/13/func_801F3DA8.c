#include "area139_13.h"

MATCH void func_801F3DA8(void) {
    u8* work;

    work                   = (u8*)g_Task;
    FIELD(u16, work, 0x30) = (FIELD(u16, work, 0x30) - 0x20);
    if ((s16)FIELD(u16, work, 0x30) < -0xFF) {
        work[2]++;
    }
    Area_Update();
}

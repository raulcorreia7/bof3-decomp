#include "boss012_16.h"

MATCH void func_800C1A24(void) {
    u8* work;

    func_800C1C08(FIELD(u16, g_SpadWork, 0x20));
    func_800C1CD8(FIELD(u16, g_SpadWork, 0x20));
    work = SPAD_WORK_BYTES;
    FIELD(u32, work, 0x20) += 2;
    if (FIELD(u32, work, 0x20) == 0x56) {
        work[3] = 3;
    }
}

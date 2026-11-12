#include "boss018_16.h"

MATCH void func_800C203C(void) {
    Actor* work;

    work = g_Task;
    FIELD(u32, work, 0x38) += (g_FrameCount & 0x1) << 9;
}

#include "boss033_16.h"

MATCH void func_800C1ED8(void) {
    Actor* work;

    work          = (Actor*)g_SpadWork;
    work->gravity = work->z.fixed + 0x4000000;
    Actor_SelectScript(2);
    SPAD_WORK_BYTES[0xB] = 0x10;
    SPAD_WORK_BYTES[2]++;
}

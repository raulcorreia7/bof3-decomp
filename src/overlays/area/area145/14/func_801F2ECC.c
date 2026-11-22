#include "area145_14.h"

MATCH void func_801F2ECC(void) {
    u8* work;

    work = TASK(u8);
    func_801F332C(work + 0xC, work + 0x18);
    g_Task->header.mode += 1;
}

#include "area041_13.h"

MATCH void func_801F3290(void) {
    if (SYS_TestFlag(D_80144EA0, 5)) {
        g_Task->timer = 0;
        g_Task->header.step += 1;
    }
    func_801F2EFC();
    func_801F3064();
}

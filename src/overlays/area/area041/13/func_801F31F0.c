#include "area041_13.h"

MATCH void func_801F31F0(void) {
    if (SYS_TestFlag(D_80144EA0, 6)) {
        g_Task->step    = 6;
        g_Task->x.fixed = -0x2940;
    } else {
        g_Task->step += 1;
        g_Task->x.fixed = -0x2B80;
    }
    g_Task->y.fixed      = -0x31C0;
    COORD_INT(g_Task->z) = -0x80;
    func_801F2EFC();
    func_801F3064();
}

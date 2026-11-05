#include "area041_13.h"

MATCH void func_801F31F0(void) {
    if (SYS_TestFlag(D_80144EA0, 6)) {
        g_SpadWork->state_02 = 6;
        g_SpadWork->x.fixed  = -0x2940;
    } else {
        g_SpadWork->state_02 += 1;
        g_SpadWork->x.fixed = -0x2B80;
    }
    g_SpadWork->y.fixed        = -0x31C0;
    g_SpadWork->z.part.integer = -0x80;
    func_801F2EFC();
    func_801F3064();
}

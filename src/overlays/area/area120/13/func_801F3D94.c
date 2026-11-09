#include "area120_13.h"

MATCH void func_801F3D94(void) {
    if ((*(u32*)g_Task->vx & 0xFFFF00) != 0x20800) {
        g_Task->header.step = 2;
    }
    func_801F3F5C(0xE0, 0x70, 2, 0);
}

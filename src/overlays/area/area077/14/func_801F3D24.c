#include "area077_14.h"

MATCH void func_801F3D24(void) {
    PushMatrix();
    if (g_Task->vx == 0xA5) {
        D_800E5502 = 1;
    }
    if (g_Task->vx >= 0x5B) {
        g_Task->pos.x.fixed = D_80146954.x.fixed;
        g_Task->pos.y.fixed = D_80146954.y.fixed;
        g_Task->pos.z.fixed = D_80146954.z.fixed;
    }
    func_801F4220();
    func_801F43C8();
    func_801F462C(0x800E4800, 0x80, 0x80, 0);
    PopMatrix();
    g_Task->vx--;
    if (g_Task->vx == 0) {
        func_80196070();
    }
}

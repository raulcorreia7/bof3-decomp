#include "area077_14.h"

MATCH void func_801F3D24(void) {
    Actor* task;

    PushMatrix();
    task = SELF(Actor);
    if (task->vx == 0xA5) {
        D_800E5502 = 1;
    }
    if (task->vx >= 0x5B) {
        task->pos.x.fixed = D_80146954.x.fixed;
        task->pos.y.fixed = D_80146954.y.fixed;
        task->pos.z.fixed = D_80146954.z.fixed;
    }
    func_801F4220();
    func_801F43C8();
    func_801F462C(MEM_PTR(s32, AREA_WORK), 128, 128, 0);
    PopMatrix();
    if (--SELF(Actor)->vx == 0) {
        func_80196070();
    }
}

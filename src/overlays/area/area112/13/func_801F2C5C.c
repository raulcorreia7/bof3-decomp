#include "area112_13.h"

/* func_801F2C5C */
MATCH void func_801F2C5C(void) {
    u8 flag_id;

    flag_id                   = D_801F420C[COORD_INT(g_Task->pos.x)];
    COORD_FRAC(g_Task->pos.x) = flag_id;
    if (SYS_TestFlag(g_SceneEventFlags, flag_id) != 0) {
        Actor* task = g_Task;

        COORD_INT(task->pos.z) = D_801F4210[COORD_INT(task->pos.x)] - 0x80;
        task->header.step      = 2;
    } else {
        Actor* task = g_Task;

        COORD_INT(task->pos.z) = D_801F4210[COORD_INT(task->pos.x)];
        task->header.step      = 4;
    }
    func_801F2EA8();
    func_801F3274();
}

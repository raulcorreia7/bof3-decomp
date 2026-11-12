#define TASK_VOLATILE
#include "area099_13.h"

MATCH void func_801F2E9C(void) {
    Actor* work;

    g_Task->timer        = 0;
    g_Task->param.unk_0B = 3;
    g_Task->unk_0A       = 16 / g_RouteSpeedScale[3];
    work                 = g_Task;
    work->vx             = 0x20000 / (work->unk_0A * 4);
    work->vy             = -0x18000 / (work->unk_0A * 4);
    work->vz             = 0x4200;
    g_Task->unk_0A       = 0xE;
    g_Task->unk_04       = 1;
    g_Game.current->u.field.unk_122 -= 2;
}

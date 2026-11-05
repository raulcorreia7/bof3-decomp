#include "area102_13.h"

MATCH void func_801F2C48(void) {
    Actor* work;

    COORD_INT(g_Task->z) = Area_SampleHeight(g_Task->x.fixed, g_Task->y.fixed);
    work                   = g_Task;
    work->unk_0A           = D_801F3944[(COORD_INT(work->x) & 1) | ((COORD_INT(work->y) & 1) << 1)];
    g_Task->unk_09         = g_Task->unk_0A + (rand() & 0x2F);
    func_801A4BC0(COORD_INT(g_Task->x), COORD_INT(g_Task->y), 0);
    g_Task->step++;
}

#include "area102_13.h"

MATCH void func_801F2C48(void) {
    Actor* work;

    g_Task->z.part.integer = Area_SampleHeight(g_Task->x.fixed, g_Task->y.fixed);
    work                   = g_Task;
    work->unk_0A           = D_801F3944[(work->x.part.integer & 1) | ((work->y.part.integer & 1) << 1)];
    g_Task->unk_09         = g_Task->unk_0A + (rand() & 0x2F);
    func_801A4BC0(g_Task->x.part.integer, g_Task->y.part.integer, 0);
    g_Task->step++;
}

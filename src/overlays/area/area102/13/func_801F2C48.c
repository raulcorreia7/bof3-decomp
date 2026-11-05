#include "area102_13.h"

MATCH void func_801F2C48(void) {
    Actor* work;

    g_SpadWork->z.part.integer = Area_SampleHeight(g_SpadWork->x.fixed, g_SpadWork->y.fixed);
    work                       = g_SpadWork;
    work->unk_0A               = D_801F3944[(work->x.part.integer & 1) | ((work->y.part.integer & 1) << 1)];
    g_SpadWork->unk_09         = g_SpadWork->unk_0A + (rand() & 0x2F);
    func_801A4BC0(g_SpadWork->x.part.integer, g_SpadWork->y.part.integer, 0);
    g_SpadWork->state_02++;
}

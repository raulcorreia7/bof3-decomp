#include "area102_13.h"

MATCH void func_801F2C48(void) {
    Actor* work;

    COORD_INT(g_Task->pos.z) = Area_SampleHeight(g_Task->pos.x.fixed, g_Task->pos.y.fixed);
    work                     = g_Task;
    work->unk_0A             = D_801F3944[(COORD_INT(work->pos.x) & 1) | ((COORD_INT(work->pos.y) & 1) << 1)];
    g_Task->unk_09           = g_Task->unk_0A + (rand() & 0x2F);
    Area_SetCellCode(COORD_INT(g_Task->pos.x), COORD_INT(g_Task->pos.y), 0);
    g_Task->header.step++;
}

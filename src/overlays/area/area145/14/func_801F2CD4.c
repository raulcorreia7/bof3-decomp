#include "area145_14.h"

MATCH void func_801F2CD4(void) {
    g_Task->pos.x.fixed = TO_COORD(49) + COORD_HALF;
    g_Task->pos.y.fixed = TO_COORD(99) + COORD_HALF;
    g_Task->gravity     = 0x500000;
    g_Task->vz          = 5242880;
    SND_QueueSelectionFx(0x208);
    g_Task->header.mode++;
    g_Task->header.step = 0;
}

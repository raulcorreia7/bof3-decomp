#include "area145_14.h"

MATCH void func_801F2CD4(void) {
    g_Task->x.fixed = 0x318000;
    g_Task->y.fixed = 0x638000;
    g_Task->gravity = 0x500000;
    g_Task->vz      = 0x500000;
    SND_QueueSelectionFx(0x208);
    g_Task->header.mode++;
    g_Task->header.step = 0;
}

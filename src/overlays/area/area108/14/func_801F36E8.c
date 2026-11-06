#include "area108_14.h"

MATCH void func_801F36E8(void) {
    Actor* work;

    g_Task->pos.x.fixed      = TO_COORD(36);
    g_Task->pos.y.fixed      = TO_COORD(65) + COORD_HALF;
    COORD_INT(g_Task->pos.z) = Area_SampleHeight(g_Task->pos.x.fixed, TO_COORD(65) + COORD_HALF);
    g_Task->unk_18           = 0;
    g_Task->tint.bytes.flags = 0x3D;
    g_Task->header.mode      = 1;
    work                     = g_Task;
    work->tint.bytes.unk_5F  = 0;
    work->tint.bytes.unk_5E  = 0;
    work->tint.bytes.unk_5D  = 0;
}

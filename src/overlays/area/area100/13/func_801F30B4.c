#include "area100_13.h"

MATCH void func_801F30B4(void) {
    Actor* work;
    s32    value;

    value         = Area_SampleHeight(FIELD(s32, g_Task, 0x34), FIELD(s32, g_Task, 0x38)) << 16;
    work          = g_Task;
    work->z.fixed = value;
    work->vz      = 0;
    work->gravity = 0;
    work->mode++;
}

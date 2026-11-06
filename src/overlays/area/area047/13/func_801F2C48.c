#include "area047_13.h"

MATCH void func_801F2C48(void) {
    Actor* actor;

    actor              = g_Task;
    actor->vx          = 60;
    actor->header.mode = actor->header.mode + 1;
}

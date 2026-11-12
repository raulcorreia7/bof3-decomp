#include "area047_13.h"
#include "area/spad.h"

MATCH void func_801F2C6C(void) {
    s32 remaining;

    remaining  = g_Task->vx - 1;
    g_Task->vx = remaining;
    if (remaining == 0) {
        g_Task->vx = 560;
        func_801F3298();
        g_Task->header.mode += 1;
    }
}

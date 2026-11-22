#include "area103_13.h"

MATCH void func_801F511C(void) {
    Actor* work = g_Task;

    work->timer++;
    if (g_Task->timer >= 0x1D) {
        Actor_Clear();
    }
}

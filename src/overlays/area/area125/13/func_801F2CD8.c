#include "area125_13.h"

MATCH void func_801F2CD8(void) {
    Actor* actor;

    func_801F33B0();
    actor = g_Task;
    actor->timer--;
    if (actor->timer == 0) {
        g_Task->header.mode++;
    }
}

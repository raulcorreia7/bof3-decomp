#include "area199_13.h"

MATCH void func_801F2CE0(void) {
    Actor* actor = g_Task;
    s32    y     = actor->pos.y.fixed;

    if (y > 0x100) {
        func_801F36DC();
    } else if (y > 0x80) {
        func_801F36DC();
        g_Task->pos.y.fixed += 2;
    } else {
        actor->pos.y.fixed = y > 0x60 ? y + 2 : y + 1;
    }
    func_801F2E80(g_Task->pos.y.fixed);
}

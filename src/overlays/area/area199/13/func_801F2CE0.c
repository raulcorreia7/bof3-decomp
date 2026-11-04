#include "area199_13.h"

MATCH void func_801F2CE0(void) {
    Actor* actor = g_SpadWork;
    s32 y        = actor->y.fixed;

    if (y > 0x100) {
        func_801F36DC();
    } else if (y > 0x80) {
        func_801F36DC();
        g_SpadWork->y.fixed += 2;
    } else {
        actor->y.fixed = y > 0x60 ? y + 2 : y + 1;
    }
    func_801F2E80(g_SpadWork->y.fixed);
}

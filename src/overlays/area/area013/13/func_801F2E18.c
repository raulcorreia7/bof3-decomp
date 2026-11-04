#include "area013_13.h"

MATCH void func_801F2E18(void) {
    Actor* actor;

    actor               = g_SpadWork;
    actor->direction_08 = (actor->direction_08 + 1) & 7;
}

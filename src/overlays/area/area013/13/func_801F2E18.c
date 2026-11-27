#include "area013_13.h"

MATCH void func_801F2E18(void) {
    Actor* actor;

    actor            = SELF(Actor);
    actor->direction = (actor->direction + 1) & 0x7;
}

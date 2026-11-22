#include "area197_13.h"

MATCH void func_801F36F0(void) {
    TASK(Actor)->timer += 1;
    if (TASK(Actor)->timer >= 16) {
        Actor_Clear();
    }
    func_801F3768(0x80 - (TASK(Actor)->timer << 3), TASK(Actor)->timer << 3);
}

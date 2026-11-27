#include "area197_13.h"

MATCH void func_801F36F0(void) {
    SELF(Actor)->timer += 1;
    if (SELF(Actor)->timer >= 16) {
        Actor_Clear();
    }
    func_801F3768(0x80 - (SELF(Actor)->timer << 3), SELF(Actor)->timer << 3);
}

#include "area198_13.h"

MATCH void func_801F2CB8(void) {
    SELF(Actor)->timer += 1;
    func_801F2D28(SELF(Actor)->timer);
    if (SELF(Actor)->timer >= 128) {
        Actor_Clear();
    }
}

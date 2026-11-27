#include "area119_13.h"

MATCH void func_801F3E94(void) {
    func_801F3F04(SELF(Actor)->timer >> 2);
    SELF(Actor)->timer--;
    if (SELF(Actor)->timer < 8) {
        Actor_Clear();
    }
}

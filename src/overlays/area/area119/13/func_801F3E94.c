#include "area119_13.h"

MATCH void func_801F3E94(void) {
    func_801F3F04(TASK(Actor)->timer >> 2);
    TASK(Actor)->timer--;
    if (TASK(Actor)->timer < 8) {
        Actor_Clear();
    }
}

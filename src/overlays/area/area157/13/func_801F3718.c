#include "area157_13.h"

MATCH void func_801F3718(void) {
    SELF(Actor)->screen_y += 0x20;
    if ((s16)SELF(Actor)->screen_y >= 0x100) {
        SELF(Actor)->header.step++;
    }
}

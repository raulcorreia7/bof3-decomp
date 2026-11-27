#include "area148_13.h"

MATCH void func_801F3720(void) {
    SELF(Actor)->screen_y = (SELF(Actor)->screen_y + 8);
    if ((s16)SELF(Actor)->screen_y >= 0x80) {
        SELF(Actor)->header.step++;
    }
    func_801F37B8(0, -1);
    func_801F37B8(1, 1);
}

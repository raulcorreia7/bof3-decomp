#include "area148_13.h"

MATCH void func_801F3720(void) {
    TASK(Actor)->screen_y = (TASK(Actor)->screen_y + 8);
    if ((s16)TASK(Actor)->screen_y >= 0x80) {
        TASK(Actor)->header.step++;
    }
    func_801F37B8(0, -1);
    func_801F37B8(1, 1);
}

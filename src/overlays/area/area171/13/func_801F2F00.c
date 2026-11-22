#include "area171_13.h"

/* Draft matches; shared slide body needs typed origin and update. */
MATCH void func_801F2F00(void) {
    u16 screen_y;

    screen_y              = TASK(Actor)->screen_y + 0x10;
    TASK(Actor)->screen_y = screen_y;
    if ((s16)screen_y >= 0xC0) {
        TASK(Actor)->header.step += 1;
    }
    func_801F3070(0);
}

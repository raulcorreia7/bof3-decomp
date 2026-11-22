#include "area082_13.h"

MATCH void func_801F34B8(void) {
    u16 scroll;
    u16 count;

    scroll                = TASK(Actor)->screen_x - 0x10;
    count                 = TASK(Actor)->unk_32 - 1;
    TASK(Actor)->unk_32   = count;
    TASK(Actor)->screen_x = scroll;
    scroll                = (count << 16) == 0;
    if (scroll) {
        Actor_Clear();
    }
}

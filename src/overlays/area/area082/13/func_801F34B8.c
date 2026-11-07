#include "area082_13.h"

MATCH void func_801F34B8(void) {
    u16 scroll;
    u16 count;

    scroll           = g_Task->screen_x - 0x10;
    count            = g_Task->unk_32 - 1;
    g_Task->unk_32   = count;
    g_Task->screen_x = scroll;
    scroll           = (count << 16) == 0;
    if (scroll) {
        Actor_Clear();
    }
}

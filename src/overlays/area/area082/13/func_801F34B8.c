#include "area082_13.h"

MATCH void func_801F34B8(void) {
    u16 scroll;
    u16 count;

    scroll             = g_SpadWork->unk_2E - 0x10;
    count              = g_SpadWork->unk_32 - 1;
    g_SpadWork->unk_32  = count;
    g_SpadWork->unk_2E  = scroll;
    scroll             = (count << 16) == 0;
    if (scroll) {
        func_80196070();
    }
}

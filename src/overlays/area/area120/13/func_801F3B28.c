#include "area120_13.h"

MATCH void func_801F3B28(void) {
    if (*(u32*)&g_GameEntryState == 0x50005) {
        g_SpadWork->state_02 += 1;
    }
    func_801F3F5C(0x80, 0x40, 1, 0);
}

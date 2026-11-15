#include "engine/slus/slus.h"

/* clears the thread's two scratch runs: the eight halfwords at 0x60 and the 16 bytes at 0x70. */
MATCH void func_8014BA04(void) {
    s32 i;

    for (i = 7; i >= 0; i--) {
        g_SysCurrentThread->unk_60[i] = 0;
    }

    for (i = 0; i < 16; i++) {
        g_SysCurrentThread->unk_70[i] = 0;
    }
}

#include "area120_13.h"

MATCH void func_801F3224(void) {
    u8* row;
    u16 i;

    row = MEM_PTR(u8, 0x800E7500u);
    for (i = 0; i < D_801F4FD4; i++) {
        *row = 3;
        row += 0xC;
    }
    SND_PlayCue(0x200);
    g_SpadWork->unk_01++;
}

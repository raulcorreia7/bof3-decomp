#include "area120_13.h"

MATCH void func_801F3224(void) {
    u8* row;
    u16 i;

    row = MEM_PTR(u8, 0x800E7500u);
    for (i = 0; i < D_801F4FD4; i++) {
        *row = 3;
        row += 12;
    }
    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x00));
    g_Task->header.mode++;
}

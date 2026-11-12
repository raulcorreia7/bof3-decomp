#include "shop_00.h"

MATCH void func_801D7380(void) {
    u8* timer;
    u8  count;
    u8  state;

    timer = &D_80148654;
    if (*timer == 6) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 2));
    }
    func_801D8050(1);
    func_801D7E1C(D_80148656, (*timer << 5) + 0x98, 63, 0, 0xFF);
    count  = *timer - 1;
    *timer = count;
    if (count == 0) {
        D_80148656          = 0;
        *timer              = 0;
        D_80148655          = 0;
        D_8014865F          = 0;
        g_MenuStep.state    = 0;
        state               = g_MenuStep.sub_step;
        g_MenuStep.sub_step = state + 1;
    }
}

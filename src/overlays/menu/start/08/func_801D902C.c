#include "start_08.h"

MATCH void func_801D902C(void) {
    u8* timer;

    Menu_DrawClutStrip(D_80144953);
    timer = &D_80148654;
    if (TIMER_EXPIRED(*timer)) {
        g_BattleChoicePhase = 2;
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 2));
        *timer = 7;
        D_80148652++;
    }
}

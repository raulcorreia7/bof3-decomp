#include "shared/etc.h"

void func_801D9110(void);

/* start_08.h cannot be included here. */
extern volatile u8 D_80148654;
extern u8          D_80148656;
extern volatile u8 D_80148665;
extern u8          D_801ED648;

MATCH void func_801D7240(void) {
    u8 state;
    u8 pending;

    Menu_DrawClutStrip(D_80144953);
    func_801D9110();
    SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 2));
    /* Volatile on the timer and the latched byte keeps the retail store order. */
    D_80148654 = 5;
    state      = D_80148651;
    pending    = D_80148665;
    D_801ED648 = 0;
    D_80148656 = pending;
    D_80148651 = state + 1;
}

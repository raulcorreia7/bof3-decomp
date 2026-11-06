#include "start_08.h"

MATCH void func_801DA8E0(void) {
    u8* timer;
    u8  i;

    Menu_DrawClutStrip(D_80144953);
    timer = &D_80148654;
    if (TIMER_EXPIRED(*timer)) {
        i = 0;
        while (i < Party_CountOrder(PARTY_ORDER_FIELD)) {
            D_8014833C[i + 4][0] = 0;
            i++;
        }
        timer = &D_80148651;
        *timer -= 2;
    }
}

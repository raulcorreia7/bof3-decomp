#include "boss051_16.h"

MATCH void func_800C1CE4(void) {
    PartyBattler* saved;

    saved      = g_SpadWork;
    g_SpadWork = D_801EB4E0;
    if (func_8014DAEC() & BYTE_MASK) {
        Actor_SelectScript(0);
        ((Actor*)g_SpadWork)->flags_24 &= 0x7F;
        ((Actor*)g_SpadWork)->unk_29 = 4;
        saved->step_01++;
    }
    g_SpadWork = saved;
}

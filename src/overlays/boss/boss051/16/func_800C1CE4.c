#include "boss051_16.h"

MATCH void func_800C1CE4(void) {
    PartyBattler* saved;

    saved  = g_Task;
    g_Task = g_BattleEffectBattler;
    if (func_8014DAEC() & BYTE_MASK) {
        Actor_SelectScript(0);
        ((Actor*)g_Task)->active_flags &= 0x7F;
        ((Actor*)g_Task)->unk_29 = 4;
        saved->header.mode++;
    }
    g_Task = saved;
}

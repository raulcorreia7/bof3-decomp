#include "boss051_16.h"

MATCH void func_800C1CE4(void) {
    PartyMember* saved;

    saved  = TASK(PartyMember);
    g_Task = g_BattleEffectBattler;
    if (Script_AnimStepOnce() & BYTE_MASK) {
        Script_Select(0);
        TASK(Actor)->active_flags &= 0x7F;
        TASK(Actor)->draw_layer = 4;
        saved->header.mode++;
    }
    g_Task = saved;
}

#include "boss051_16.h"

MATCH void func_800C1CE4(void) {
    PartyMember* saved;

    saved  = SELF(PartyMember);
    g_Self = g_BattleEffectBattler;
    if (Script_AnimStepOnce() & BYTE_MASK) {
        Script_Select(0);
        SELF(Actor)->active_flags &= 0x7F;
        SELF(Actor)->draw_layer = 4;
        saved->header.mode++;
    }
    g_Self = saved;
}

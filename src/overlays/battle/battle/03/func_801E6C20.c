#include "battle_03.h"

MATCH void func_801E6C20(void) {
    volatile u16* gate;
    u8            count;
    u16           half;

    Script_AnimStepOnce();
    count                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = count;
    if (count == 0u) {
        gate        = &g_Battle.flags;
        half        = (*gate | 0x20u);
        *(u16*)gate = half;
        Effect_Reset();
    }
}

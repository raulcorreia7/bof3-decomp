#include "magic079_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    ACTOR_RUN_MODE_HANDLER(func_801EEC5C, func_801EED38);
}

MATCH void func_801EEC5C(void) {
    u8           i;
    u32          slot;
    PartyMember* work;

    SELF(PartyMember)->param.unk_0B = 0;
    for (i = 0; i < 4; i++) {
        slot                               = Battle_AllocEffect(1, 43) & BYTE_MASK;
        work                               = SELF(PartyMember);
        g_BattleEffects[slot].header.mode  = i;
        g_BattleEffects[slot].header.step  = 0;
        g_BattleEffects[slot].arg.unk_09   = 0x10;
        g_BattleEffects[slot].target.party = work;
        SELF(PartyMember)->param.unk_0B    = SELF(PartyMember)->param.unk_0B + 1;
    }
    SND_SEQueueSelection(0x100);
    SELF(PartyMember)->header.mode = SELF(PartyMember)->header.mode + 1;
}

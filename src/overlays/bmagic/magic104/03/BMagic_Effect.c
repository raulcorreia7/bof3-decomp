#include "magic104_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC14.h"

INCLUDE_ASM(func_801EEC80);

INCLUDE_ASM(func_801EEE7C);

INCLUDE_ASM(func_801EEEC0);

MATCH void func_801EF03C(void) {
    if (g_SpadWork->word_08.byte.unk_0B == 7) {
        func_800A9820(g_BattleTargetSelector);
        g_BattleState |= BATTLE_STATE_EFFECT_PLAYING;
        func_801E5988();
    }
}

MATCH void func_801EF09C(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

INCLUDE_ASM(func_801EF0E0);

INCLUDE_ASM(func_801EF178);

INCLUDE_ASM(func_801EF21C);

/* Template: bmagic/magic040 func_801EF114; size 0x6C against retail 0x7C, first difference lbu v0,9(v1) at +0x0C. */
INCLUDE_ASM(func_801EF27C);

MATCH void func_801EF2F8(void) {
    PartyBattler* work;
    PartyBattler* active;

    work                        = g_SpadWork;
    work->word_08.byte.timer_0A = work->word_08.byte.timer_0A + 1;
    work                        = g_SpadWork;
    work->word_08.byte.unk_09   = work->word_08.byte.unk_09 + 1;
    if (work->word_08.byte.unk_09 == 0x18) {
        active                      = BATTLE_ACTIVE_WORK;
        active->word_08.byte.unk_0B = g_SpadWork->word_08.byte.unk_0B;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF370);

INCLUDE_ASM(func_801EFA54);

INCLUDE_ASM(func_801EFB2C);

INCLUDE_ASM(func_801EFE34);

INCLUDE_ASM(func_801F020C);

INCLUDE_ASM(func_801F02F4);

INCLUDE_ASM(func_801F034C);

INCLUDE_ASM(func_801F03C4);

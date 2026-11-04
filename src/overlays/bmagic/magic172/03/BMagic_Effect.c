#include "magic172_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    Callback handlers[2] = {func_801EEC5C, func_801EEDD8};

    SYS_DISPATCH_TASK(handlers, 1, g_SpadWork);
}

INCLUDE_ASM(func_801EEC5C);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EEE38(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

INCLUDE_ASM(func_801EEE7C);

INCLUDE_ASM(func_801EF158);

INCLUDE_ASM(func_801EF210);

INCLUDE_ASM(func_801EF3A4);

INCLUDE_ASM(func_801EF430);

MATCH void func_801EF4BC(void) {
    PartyBattler* work;

    work = g_SpadWork;
    work->unk_09 -= 2;
    if (work->unk_09 == 0) {
        work = (PartyBattler*)D_801EB4E0;
        work->unk_0B--;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF518);

INCLUDE_ASM(func_801EF590);

INCLUDE_ASM(func_801EF650);

/* needs: type. Effect_TickOnTimerZero shape; retail tests the work byte as signed (sll 24, bgez after a -2 step) where the unk_09 member is u8 in PartyBattler; first differing instruction is andi v0,v0,0xff against sll v0,v0,24. */
INCLUDE_ASM(func_801EF770);

INCLUDE_ASM(func_801EF7CC);

INCLUDE_ASM(func_801EFA2C);

INCLUDE_ASM(func_801EFD04);

INCLUDE_ASM(func_801EFFE8);

INCLUDE_ASM(func_801F02C8);

INCLUDE_ASM(func_801F05E8);

INCLUDE_ASM(func_801F0908);

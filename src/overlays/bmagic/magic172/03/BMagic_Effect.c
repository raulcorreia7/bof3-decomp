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

#include "overlays/bmagic/Effect_TickOnTimerZero.h"
INCLUDE_ASM(func_801EF518);

INCLUDE_ASM(func_801EF590);

INCLUDE_ASM(func_801EF650);

#include "overlays/bmagic/Effect_TickOnTimerNegative.h"

INCLUDE_ASM(func_801EF7CC);

INCLUDE_ASM(func_801EFA2C);

INCLUDE_ASM(func_801EFD04);

INCLUDE_ASM(func_801EFFE8);

INCLUDE_ASM(func_801F02C8);

INCLUDE_ASM(func_801F05E8);

INCLUDE_ASM(func_801F0908);

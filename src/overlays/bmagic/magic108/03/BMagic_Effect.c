#include "magic108_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    Callback handlers[2] = {func_801EEC5C, func_801EED1C};
    SYS_DISPATCH_TASK(handlers, 1, g_SpadWork);
}

INCLUDE_ASM(func_801EEC5C);

#include "overlays/bmagic/Effect_PlayOnIdleTick.h"

INCLUDE_ASM(func_801EED7C);

INCLUDE_ASM(func_801EEE0C);

INCLUDE_ASM(func_801EEF48);

INCLUDE_ASM(func_801EF020);

INCLUDE_ASM(func_801EF090);

MATCH void func_801EF0E0(void) {
    u8 timer;

    timer                             = g_SpadWork->word_08.byte.timer_0A + 1;
    g_SpadWork->word_08.byte.timer_0A = timer;
    if (timer == 96) {
        g_SpadWork->step_01 = g_SpadWork->step_01 + 1;
    }
}

INCLUDE_ASM(func_801EF130);

INCLUDE_ASM(func_801EF180);

INCLUDE_ASM(func_801EF2D4);

INCLUDE_ASM(func_801EF5C0);

INCLUDE_ASM(func_801EF6C0);

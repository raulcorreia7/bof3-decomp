#include "magic122_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    Callback handlers[2] = {func_801EEC5C, func_801EEDFC};
    SYS_DISPATCH_TASK(handlers, 1, g_SpadWork);
}

INCLUDE_ASM(func_801EEC5C);

#include "overlays/bmagic/Effect_PlayOnIdleTick.h"

MATCH void func_801EEE5C(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_SpadWork->step_01);
}

INCLUDE_ASM(func_801EEEA0);

INCLUDE_ASM(func_801EEF2C);

MATCH void func_801EF158(void) {
    PartyBattler* work;

    work = g_SpadWork;
    work->word_08.byte.timer_0A += 3;
    work = g_SpadWork;
    work->word_08.byte.unk_09++;
    if (work->word_08.byte.unk_09 == 8) {
        work = g_SpadWork;
        work->unk_02++;
    }
}

#include "overlays/bmagic/Effect_CountUpTimerCallSelector.h"

#include "overlays/bmagic/Effect_CountUpAndStepAt120.h"

MATCH void func_801EF29C(void) {
    u8 counter;

    g_SpadWork->word_08.byte.unk_0B += 1;
    g_SpadWork->unk_04 -= 1;
    counter                         = g_SpadWork->word_08.byte.unk_09 + 1;
    g_SpadWork->word_08.byte.unk_09 = counter;
    if ((counter & 0xFF) == 0x88) {
        BATTLE_ACTIVE_WORK->word_08.byte.unk_0B = 0xFF;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF324);

INCLUDE_ASM(func_801EFBA8);

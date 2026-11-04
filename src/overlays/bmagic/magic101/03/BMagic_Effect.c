#include "magic101_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC18(void) {
    BattleHandlerTable5 handlers;

    handlers = D_801EEC04;
    SYS_DISPATCH_BYTE(handlers.handlers, g_SpadWork->step_01);
    if (g_SpadWork->word_08.byte.timer_0A != 0 && g_SpadWork->flags_00 != 0) {
        Effect_SetActorMatrix();
        func_801EF07C();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EECCC);

MATCH void func_801EEE68(void) {
    u8 timer;

    timer                             = g_SpadWork->word_08.byte.timer_0A + 1;
    g_SpadWork->word_08.byte.timer_0A = timer;
    if (timer == 16) {
        func_800A9610(g_BattleTargetSelector, 0x10);
        g_SpadWork->step_01 = g_SpadWork->step_01 + 1;
    }
}

#include "overlays/bmagic/Effect_CountDownTimerNextStep.h"

MATCH void func_801EEF20(void) {
    u8 timer;

    timer                             = g_SpadWork->word_08.byte.timer_0A - 1;
    g_SpadWork->word_08.byte.timer_0A = timer;
    if (timer == 0) {
        g_SpadWork->step_01 = g_SpadWork->step_01 + 1;
    }
}

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801EF07C);

MATCH void func_801EF310(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

MATCH void func_801EF354(void) {
    SYS_DISPATCH_BYTE(D_801EFCE8, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        func_801EF78C();
        func_801EF88C();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EF3DC);

INCLUDE_ASM(func_801EF4DC);

INCLUDE_ASM(func_801EF580);

INCLUDE_ASM(func_801EF690);

INCLUDE_ASM(func_801EF700);

INCLUDE_ASM(func_801EF78C);

INCLUDE_ASM(func_801EF88C);

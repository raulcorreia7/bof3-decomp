#include "magic039_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_RunStep.h"

INCLUDE_ASM(func_801EEC94);

#include "overlays/bmagic/Effect_NextStepOnWorkZeroTick.h"

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

INCLUDE_ASM(func_801EEF3C);

MATCH void func_801EEF64(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

INCLUDE_ASM(func_801EEFA8);

MATCH void func_801EF070(void) {
    PartyBattler* src;

    src                               = (PartyBattler*)D_801EB4E0;
    g_SpadWork->coord_x_34            = src->coord_x_34;
    g_SpadWork->coord_y_38            = src->coord_y_38;
    g_SpadWork->word_3C               = src->word_3C;
    g_SpadWork->word_08.byte.unk_09   = 0;
    g_SpadWork->word_08.byte.timer_0A = 1;
    g_SpadWork->unk_02                = g_SpadWork->unk_02 + 1;
}

INCLUDE_ASM(func_801EF0D4);

INCLUDE_ASM(func_801EF134);

INCLUDE_ASM(func_801EF1F4);

INCLUDE_ASM(func_801EF320);

INCLUDE_ASM(func_801EF44C);

MATCH void func_801EF4E4(void) {
    BattleHandlerTable3 handlers;

    handlers = D_801EEC28;
    SYS_DISPATCH_BYTE(handlers.handlers, g_SpadWork->unk_02);
    if (ACTOR_IN_USE(*g_SpadWork) && g_SpadWork->unk_02 != 0) {
        func_800AF764();
        func_801EF758();
    }
}

INCLUDE_ASM(func_801EF584);

MATCH void func_801EF690(void) {
    u8 timer;

    timer                           = g_SpadWork->word_08.byte.unk_09 + 16;
    g_SpadWork->word_08.byte.unk_09 = timer;
    if (timer == 128) {
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 1;
    }
}

#include "overlays/bmagic/Effect_CountDownTimer.h"

INCLUDE_ASM(func_801EF758);

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801EFAA4);

INCLUDE_ASM(func_801F0054);

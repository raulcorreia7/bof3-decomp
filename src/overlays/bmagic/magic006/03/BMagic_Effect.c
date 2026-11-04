#include "magic006_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC38(void) {
    Bmagic_DispatchTaskPair(func_801EEC90, func_801EEDA4);
}

INCLUDE_ASM(func_801EEC90);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EEE04(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

INCLUDE_ASM(func_801EEE48);

MATCH void func_801EEF28(void) {
    PartyBattler* battler;
    u8            value;

    value                           = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = value;
    if (!(value & 0xFF)) {
        g_SpadWork->coord_x_34.raw = D_801EB4E0->coord_x_34.raw;
        g_SpadWork->coord_y_38.raw = D_801EB4E0->coord_y_38.raw;
        g_SpadWork->word_3C.word   = D_801EB4E0->word_3C.word + 0x800000;
        func_800AF764(g_SpadWork);
        battler            = g_BattleSelectedActor;
        g_SpadWork->unk_0C = ratan2(battler->coord_x_34.raw - g_SpadWork->coord_x_34.raw,
                                    battler->coord_y_38.raw - g_SpadWork->coord_y_38.raw);
        g_SpadWork->unk_10 = 0;
        g_SpadWork->unk_14 = (ratan2((s16)battler->unk_2E.half - (s16)g_SpadWork->unk_2E.half,
                                     (s16)battler->unk_30.half - (s16)g_SpadWork->unk_30.half) -
                              0x200) &
                             0xFFF;
        SND_QueueSelectionFx(0x100);
        g_SpadWork->word_08.byte.unk_09 = 0x20;
        g_SpadWork->unk_02 += 1;
    }
}

INCLUDE_ASM(func_801EF04C);

MATCH void func_801EF0B8(void) {
    PartyBattler* work;

    work                      = g_SpadWork;
    work->word_08.byte.unk_09 = work->word_08.byte.unk_09 - 1;
    if (work->word_08.byte.unk_09 == 0) {
        SND_QueueSelectionFx(0x101);
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 1;
    }
}

INCLUDE_ASM(func_801EF118);

INCLUDE_ASM(func_801EF298);

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

INCLUDE_ASM(func_801EF478);

INCLUDE_ASM(func_801EFB6C);

MATCH void func_801F0064(void) {
    BattleHandlerTable3 handlers;

    handlers = D_801EEC1C;
    SYS_DISPATCH_BYTE(handlers.handlers, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        func_800AF764();
        func_801F0308();
    }
}

INCLUDE_ASM(func_801F0100);

INCLUDE_ASM(func_801F020C);

#include "overlays/bmagic/Effect_CountDownTimer.h"

INCLUDE_ASM(func_801F0308);

MATCH void func_801F04F4(void) {
    MagicTaskFuncs handlers;

    handlers = D_801EEC28;
    SYS_DISPATCH_BYTE(handlers.handlers, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        Effect_SetActorMatrix();
        func_801F0790();
        PopMatrix();
    }
}

MATCH void func_801F05A4(void) {
    PartyBattler* src;

    src                             = g_BattleSelectedActor;
    g_SpadWork->coord_x_34          = src->coord_x_34;
    g_SpadWork->coord_y_38          = src->coord_y_38;
    g_SpadWork->word_3C             = src->word_3C;
    g_SpadWork->word_08.byte.unk_09 = 0;
    g_SpadWork->unk_02              = g_SpadWork->unk_02 + 1;
}

MATCH void func_801F05F4(void) {
    u8 timer;

    timer                           = g_SpadWork->word_08.byte.unk_09 + 4;
    g_SpadWork->word_08.byte.unk_09 = timer;
    if (timer == 16) {
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 1;
    }
}

#include "overlays/bmagic/Effect_NextStepOnLastTick.h"

MATCH void Effect_TickOnTimerZero_801F0684(void) {
    PartyBattler* work;

    BMAGIC_TICK_ON_TIMER_ZERO(EFFECT_TIMER_TICK);
}

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801F0790);

#include "magic103_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_RunStep.h"

INCLUDE_ASM(func_801EEC70);

INCLUDE_ASM(func_801EEE38);

#include "shared/Effect_StartPlaying.h"

MATCH void func_801EEEC8(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

MATCH void func_801EEF0C(void) {
    SYS_DISPATCH_BYTE(D_801F07A0, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        Effect_SetActorMatrix();
        func_801EF1D8();
        PopMatrix();
    }
}

MATCH void func_801EEF94(void) {
    PartyBattler* src;

    src                               = g_BattleSelectedActor;
    g_SpadWork->coord_x_34            = src->coord_x_34;
    g_SpadWork->coord_y_38            = src->coord_y_38;
    g_SpadWork->word_3C.half.span_3E  = src->word_3C.half.span_3E;
    g_SpadWork->word_08.byte.unk_09   = 0;
    g_SpadWork->word_08.byte.timer_0A = 0;
    g_SpadWork->unk_02                = g_SpadWork->unk_02 + 1;
}

INCLUDE_ASM(func_801EEFF4);

INCLUDE_ASM(func_801EF094);

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801EF1D8);

INCLUDE_ASM(func_801EF7CC);

MATCH void func_801EFB10(void) {
    SYS_DISPATCH_BYTE(D_801F07C4, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        func_801EFE20();
    }
}

MATCH void func_801EFB88(void) {
    PartyBattler* work;
    u8            timer;

    timer                           = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = timer;
    if (timer == 0) {
        work                      = g_SpadWork;
        work->coord_x_34.raw      = g_BattleSelectedActor->coord_x_34.raw + D_801F07AC[work->word_08.byte.unk_0B].x;
        work->coord_y_38.raw      = g_BattleSelectedActor->coord_y_38.raw + D_801F07AC[work->word_08.byte.unk_0B].y;
        work->word_3C.word        = g_BattleSelectedActor->word_3C.word + D_801F07AC[work->word_08.byte.unk_0B].z;
        work->word_08.byte.unk_09 = 0;
        g_SpadWork->word_08.byte.timer_0A = 0;
        g_SpadWork->unk_02 += 1;
    }
}

INCLUDE_ASM(func_801EFC70);

INCLUDE_ASM(func_801EFCF4);

INCLUDE_ASM(func_801EFD74);

INCLUDE_ASM(func_801EFE20);

MATCH void func_801F02BC(void) {
    SYS_DISPATCH_BYTE(D_801F07D4, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        Effect_SetActorMatrix();
        func_801F04E0();
        PopMatrix();
    }
}

MATCH void func_801F0344(void) {
    PartyBattler* src;

    src                               = g_BattleSelectedActor;
    g_SpadWork->coord_x_34            = src->coord_x_34;
    g_SpadWork->coord_y_38            = src->coord_y_38;
    g_SpadWork->word_3C               = src->word_3C;
    g_SpadWork->word_08.byte.unk_09   = 0;
    g_SpadWork->word_08.byte.timer_0A = 0;
    g_SpadWork->unk_02                = g_SpadWork->unk_02 + 1;
}

MATCH void func_801F03A4(void) {
    PartyBattler* work;

    work = g_SpadWork;
    work->word_08.byte.timer_0A += 2;
    work = g_SpadWork;
    work->word_08.byte.unk_09++;
    if (work->word_08.byte.unk_09 == 8) {
        work = g_SpadWork;
        work->unk_02++;
    }
}

MATCH void func_801F0410(void) {
    u8 timer;

    timer                           = g_SpadWork->word_08.byte.unk_09 + 1;
    g_SpadWork->word_08.byte.unk_09 = timer;
    if (timer == 30) {
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 1;
    }
}

#include "overlays/bmagic/Effect_CountDownTimerCapped.h"

INCLUDE_ASM(func_801F04E0);

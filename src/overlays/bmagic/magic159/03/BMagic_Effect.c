#include "magic159_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    Callback handlers[2] = {func_801EEC5C, func_801EED84};

    SYS_DISPATCH_TASK(handlers, 1, g_Task);
}

INCLUDE_ASM(func_801EEC5C);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EEDE4(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_Task->mode);
}

INCLUDE_ASM(func_801EEE28);

MATCH void func_801EEEC8(void) {
    PartyBattler* src;
    PartyBattler* dst;

    if (--g_Task->word_08.byte.unk_09 == 0) {
        src                           = D_801EB4E0;
        dst                           = g_Task;
        dst->coord_x_34               = src->coord_x_34;
        dst->coord_y_38               = src->coord_y_38;
        dst->word_3C                  = src->word_3C;
        dst->word_08.byte.unk_09      = 0x10;
        g_Task->word_08.byte.timer_0A = 0;
        g_Task->step++;
    }
}

MATCH void func_801EEF58(void) {
    PartyBattler* work;

    work = g_Task;
    work->word_08.byte.unk_09++;
    work = g_Task;
    work->word_08.byte.timer_0A += 2;
    if (work->word_08.byte.timer_0A == 16) {
        work = g_Task;
        work->step++;
    }
}

MATCH void func_801EEFC4(void) {
    u8 timer;

    timer                       = g_Task->word_08.byte.unk_09 + 1;
    g_Task->word_08.byte.unk_09 = timer;
    if (timer > 0x20) {
        g_Task->step = g_Task->step + 1;
    }
}

MATCH void func_801EF014(void) {
    PartyBattler* work;
    PartyBattler* active;
    u8            count;

    work = g_Task;
    work->word_08.byte.unk_09++;
    work                        = g_Task;
    count                       = work->word_08.byte.timer_0A - 2;
    work->word_08.byte.timer_0A = count;
    if (count == 0) {
        active = BATTLE_ACTIVE_WORK;
        active->word_08.byte.unk_0B--;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF08C);

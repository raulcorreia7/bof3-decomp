#include "magic055_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC10);

INCLUDE_ASM(func_801EECCC);

#include "overlays/bmagic/func_801EEE3C.h"

INCLUDE_ASM(func_801EEEA8);

#include "overlays/bmagic/func_801EEF74.h"

MATCH void func_801EEFFC(void) {
    u8            timer;
    PartyBattler* src;
    PartyBattler* work;

    timer              = g_SpadWork->unk_09 - 1;
    g_SpadWork->unk_09 = timer;
    if (timer == 0) {
        src                 = BATTLE_ACTIVE_WORK;
        work                = g_SpadWork;
        work->coord_x_34    = src->coord_x_34;
        work->coord_y_38    = src->coord_y_38;
        work->word_3C       = src->word_3C;
        work->unk_09        = 0x40;
        g_SpadWork->unk_0A  = 0;
        g_SpadWork->unk_0B  = 0;
        g_SpadWork->step_01 = g_SpadWork->step_01 + 1;
    }
}

INCLUDE_ASM(func_801EF09C);

INCLUDE_ASM(func_801EF124);

INCLUDE_ASM(func_801EF1B8);

INCLUDE_ASM(func_801EF240);

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801EF7B0);

INCLUDE_ASM(func_801EF9E4);

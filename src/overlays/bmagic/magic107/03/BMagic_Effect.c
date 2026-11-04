#include "magic107_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    Callback table[2] = {func_801EEC5C, func_801EED40};

    table[SP_REF(u8*, 0x44)[1]]();
}

INCLUDE_ASM(func_801EEC5C);

#include "overlays/bmagic/Effect_PlayOnIdleTick.h"

INCLUDE_ASM(func_801EEDA0);

MATCH void func_801EEE50(void) {
    g_SpadWork->word_08.byte.unk_0B   = 0;
    g_SpadWork->word_08.byte.unk_09   = 0;
    g_SpadWork->word_08.byte.timer_0A = 0;
    g_SpadWork->step_01++;
}

MATCH void func_801EEEA0(void) {
    g_SpadWork->word_08.byte.unk_09 += 1;
    g_SpadWork->word_08.byte.timer_0A += 1;
    if (g_SpadWork->word_08.byte.unk_09 == 0x20) {
        g_SpadWork->step_01 = g_SpadWork->step_01 + 1;
    }
}

MATCH void func_801EEF0C(void) {
    g_SpadWork->word_08.byte.unk_09 += 1;
    if (g_SpadWork->word_08.byte.unk_09 == 0xC0) {
        g_SpadWork->step_01 += 1;
    }
}

MATCH void func_801EEF5C(void) {
    PartyBattler* active;

    g_SpadWork->word_08.byte.unk_09   = g_SpadWork->word_08.byte.unk_09 + 1;
    g_SpadWork->word_08.byte.timer_0A = g_SpadWork->word_08.byte.timer_0A - 1;
    if (g_SpadWork->word_08.byte.timer_0A == 0) {
        active                      = BATTLE_ACTIVE_WORK;
        active->word_08.byte.unk_0B = 255;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EEFD4);

INCLUDE_ASM(func_801EF0E4);

INCLUDE_ASM(func_801EF290);

INCLUDE_ASM(func_801EF544);

#include "overlays/bmagic/Effect_SetActorMatrixQuarterRoll.h"

INCLUDE_ASM(func_801EFAE0);

INCLUDE_ASM(func_801EFEA8);

INCLUDE_ASM(func_801F01AC);

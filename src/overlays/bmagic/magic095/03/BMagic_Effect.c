#include "magic095_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC18);

INCLUDE_ASM(func_801EEC9C);

INCLUDE_ASM(func_801EEE60);

MATCH void func_801EEF64(void) {
    u8 counter;

    func_801EF1FC();
    func_801EF804();
    func_801EFDDC();
    counter                         = g_SpadWork->word_08.byte.unk_09 + 1;
    g_SpadWork->word_08.byte.unk_09 = counter;
    if ((counter & 0xFF) == 0x40) {
        SND_QueueSelectionFx(0x101);
        SND_QueueSelectionFx(0x102);
        g_SpadWork->word_08.byte.unk_09 = 0x30;
        g_SpadWork->step_01 += 1;
    }
}

MATCH void func_801EEFFC(void) {
    u8 timer;

    func_801EF1FC();
    func_801EF804();
    func_801EFDDC();
    timer                           = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = timer;
    if (timer == 0) {
        g_SpadWork->step_01 = g_SpadWork->step_01 + 1;
    }
}

MATCH void func_801EF070(void) {
    u8            timer;
    u32           slot;
    u8*           selector;
    PartyBattler* battler;

    func_801EFDDC();
    timer                             = g_SpadWork->word_08.byte.timer_0A - 1;
    g_SpadWork->word_08.byte.timer_0A = timer;
    if (timer == 0) {
        BMAGIC_RELEASE_TARGET_AND_PLAY();
    }
}

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801EF1FC);

INCLUDE_ASM(func_801EF804);

INCLUDE_ASM(func_801EFDDC);

INCLUDE_ASM(func_801F0018);

MATCH void func_801F0070(void) {
    u8 counter;

    if (BATTLE_ACTIVE_WORK->step_01 == 3) {
        counter                         = g_SpadWork->word_08.byte.unk_09 - 1;
        g_SpadWork->word_08.byte.unk_09 = counter;
        if (!(counter & 0xFF)) {
            g_SpadWork->step_01 += 1;
        }
    }
}

MATCH void func_801F00D8(void) {
    u8 temp_v1;

    func_801F012C();
    temp_v1                         = g_SpadWork->word_08.byte.unk_09 + 1;
    g_SpadWork->word_08.byte.unk_09 = temp_v1;
    if ((temp_v1 & 0xFF) == 0x20) {
        func_801E5988();
    }
}

INCLUDE_ASM(func_801F012C);

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

MATCH void func_801EED7C(void) {
    SYS_DISPATCH_BYTE(D_801EFC9C, g_SpadWork->step_01);
    if (g_SpadWork->flags_00 != 0) {
        func_801EF5C0();
        func_801EF6C0();
        PopMatrix();
        func_801EF180();
        func_801EF2D4();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EEE0C);

INCLUDE_ASM(func_801EEF48);

MATCH void func_801EF020(void) {
    u8 temp_v0;

    temp_v0                           = g_SpadWork->word_08.byte.timer_0A + 1;
    g_SpadWork->word_08.byte.timer_0A = temp_v0;
    if (!(temp_v0 & 0x1F)) {
        SND_QueueSelectionFx(0x101);
        g_SpadWork->word_08.byte.timer_0A = 0;
        g_SpadWork->step_01 += 1;
    }
}

#include "overlays/bmagic/Effect_AdvanceOnTick.h"

MATCH void func_801EF0E0(void) {
    u8 timer;

    timer                             = g_SpadWork->word_08.byte.timer_0A + 1;
    g_SpadWork->word_08.byte.timer_0A = timer;
    if (timer == 96) {
        g_SpadWork->step_01 = g_SpadWork->step_01 + 1;
    }
}

MATCH void func_801EF130(void) {
    u8 temp_v1;

    temp_v1                           = g_SpadWork->word_08.byte.timer_0A + 1;
    g_SpadWork->word_08.byte.timer_0A = temp_v1;
    if ((temp_v1 & 0xFF) == 0x80) {
        D_801EB4E0->word_08.byte.unk_0B = 0xFF;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF180);

INCLUDE_ASM(func_801EF2D4);

INCLUDE_ASM(func_801EF5C0);

INCLUDE_ASM(func_801EF6C0);

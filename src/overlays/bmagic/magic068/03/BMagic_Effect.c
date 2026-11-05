#include "magic068_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC18.h"

INCLUDE_ASM(func_801EEC88);

INCLUDE_ASM(func_801EED50);

MATCH void func_801EF44C(void) {
    u8 timer;

    timer                             = g_SpadWork->word_08.byte.timer_0A - 1;
    g_SpadWork->word_08.byte.timer_0A = timer;
    if (timer == 0) {
        g_SpadWork->word_08.byte.timer_0A = 0x3E;
        g_SpadWork->step_01               = g_SpadWork->step_01 + 1;
    }
}

MATCH void func_801EF4A8(void) {
    func_801EF55C();
    if (g_InputPressed != 0) {
        g_SpadWork->step_01 = 4;
    }
}

INCLUDE_ASM(func_801EF4EC);

INCLUDE_ASM(func_801EF55C);

MATCH void func_801EF73C(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

MATCH void func_801EF780(void) {
    SYS_DISPATCH_TASK(g_BMagicEffectFuncs + 1, 2, g_SpadWork);
}

MATCH void func_801EF7C4(void) {
    g_SpadWork->word_08.byte.facing_08 = D_801EB4E0->word_08.byte.facing_08;
    g_SpadWork->coord_x_34.raw         = D_801EB4E0->coord_x_34.raw;
    g_SpadWork->coord_y_38.raw         = D_801EB4E0->coord_y_38.raw;
    g_SpadWork->word_3C.word           = D_801EB4E0->word_3C.word + 0x02000000;
    func_800AF764(g_SpadWork);
    SND_QueueSelectionFx(0x100);
    g_SpadWork->word_08.byte.unk_0B   = 0;
    g_SpadWork->word_08.byte.unk_09   = 0xF;
    g_SpadWork->word_08.byte.timer_0A = 3;
    g_SpadWork->unk_02 += 1;
}

MATCH void func_801EF884(void) {
    u8 temp_v0;

    Effect_SetActorMatrix();
    func_801EFA48();
    PopMatrix();
    temp_v0                         = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        g_SpadWork->word_08.byte.unk_09 = 0xF;
        g_SpadWork->unk_02 += 1;
    }
}

INCLUDE_ASM(func_801EF908);

MATCH void func_801EF9D0(void) {
    u8 timer;

    Effect_SetActorMatrix();
    func_801EFA48();
    PopMatrix();
    timer                           = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = timer;
    if (timer == 0) {
        BMAGIC_TICK_EFFECT_WORK();
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EFA48);

#include "overlays/bmagic/Effect_SetActorMatrix.h"

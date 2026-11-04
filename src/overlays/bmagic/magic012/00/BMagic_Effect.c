#include "magic012_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    Bmagic_DispatchTaskPair(func_801EEC5C, func_801EEEAC);
}

INCLUDE_ASM(func_801EEC5C);

INCLUDE_ASM(func_801EEEAC);

MATCH void func_801EEFF8(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

MATCH void func_801EF03C(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectFuncs + 1), 2, g_SpadWork);
}

MATCH void func_801EF080(void) {
    u8 temp_v0;

    temp_v0            = g_SpadWork->unk_09 - 1;
    g_SpadWork->unk_09 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        g_SpadWork->unk_08 = D_801EB4E0->unk_08;
        g_SpadWork->unk_0C = 0x20000;
        g_SpadWork->unk_10 = 0;
        func_801DD350(g_SpadWork);
        g_SpadWork->coord_x_34.raw       = D_801EB4E0->coord_x_34.raw + g_SpadWork->unk_0C;
        g_SpadWork->coord_y_38.raw       = D_801EB4E0->coord_y_38.raw + g_SpadWork->unk_10;
        g_SpadWork->word_3C.half.span_3E = (u16)D_801EB4E0->word_3C.half.span_3E + 0x100;
        g_SpadWork->unk_0B               = rand() & 7;
        g_SpadWork->unk_09               = 0x10;
        g_SpadWork->unk_0A               = 0;
        g_SpadWork->unk_02 += 1;
    }
}

INCLUDE_ASM(func_801EF188);

INCLUDE_ASM(func_801EF3C4);

INCLUDE_ASM(func_801EF4B8);

MATCH void func_801EF670(void) {
    BMAGIC_TICK_EFFECT_WORK();
    func_801E5988();
}

INCLUDE_ASM(func_801EF6A4);

INCLUDE_ASM(func_801EF79C);

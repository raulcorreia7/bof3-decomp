#include "magic158_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC04);

INCLUDE_ASM(func_801EED04);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EEEF0(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

MATCH void func_801EEF34(void) {
    SYS_DISPATCH_BYTE(D_801EF788, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        func_801EF2F0();
        func_801EF3EC();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EEFBC);

MATCH void func_801EF140(void) {
    u8 temp_a0;
    u8 temp_v0;

    temp_a0                          = g_SpadWork->word_08.byte.unk_09;
    g_SpadWork->word_3C.half.span_3E = (u16)g_SpadWork->word_3C.half.span_3E - 0x60;
    if ((temp_a0 & 0xFF) != 0x10) {
        g_SpadWork->word_08.byte.unk_09 = temp_a0 + 1;
    }
    temp_v0 = g_SpadWork->word_08.byte.timer_0A;
    if (temp_v0 != 0x10) {
        g_SpadWork->word_08.byte.timer_0A = temp_v0 + 2;
    }
    if (g_SpadWork->word_3C.half.span_3E == BATTLE_ACTIVE_WORK->word_3C.half.span_3E) {
        g_SpadWork->unk_02 += 1;
    }
}

INCLUDE_ASM(func_801EF1C8);

INCLUDE_ASM(func_801EF2F0);

INCLUDE_ASM(func_801EF3EC);

/* func_801EF708 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

#include "magic074_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC28);

INCLUDE_ASM(func_801EED18);

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

MATCH void func_801EEF9C(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

MATCH void func_801EEFE0(void) {
    BmagicEffectFuncs handlers;

    BMAGIC_DISPATCH_STEP_HANDLERS(D_801EEC04, unk_02);
}

INCLUDE_ASM(func_801EF058);

INCLUDE_ASM(func_801EF2C8);

INCLUDE_ASM(func_801EF3C0);

/* func_801EF4D0 */
#include "overlays/bmagic/Effect_NextStepUnderTickLimit.h"

INCLUDE_ASM(func_801EF518);

INCLUDE_ASM(func_801EF6A4);

MATCH void func_801EF710(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectFuncs + 1), 1, D_801F20DC);
}

INCLUDE_ASM(func_801EF754);

INCLUDE_ASM(func_801EF850);

INCLUDE_ASM(func_801EFA50);

MATCH void func_801EFB00(void) {
    u16 phase;
    u8  timer;

    BMAGIC_SWAY_EFFECT_WORK(D_801F20DC, func_801F0440)
}

INCLUDE_ASM(func_801EFBE4);

INCLUDE_ASM(func_801EFE18);

INCLUDE_ASM(func_801F00B0);

INCLUDE_ASM(func_801F03D4);

MATCH void func_801F0440(void) {
    D_801F20DC->flags_00 = 0;
    D_801F20DC->step_01  = 0;
    D_801F20DC->unk_02   = 0;
    D_801F20DC->unk_03   = 0;
    D_801F20DC->unk_04   = 0;
}

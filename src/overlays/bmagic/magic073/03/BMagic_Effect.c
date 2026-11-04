#include "magic073_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC28);

INCLUDE_ASM(func_801EED18);

MATCH void func_801EEF50(void) {
    u16* flags;

    if (g_SpadWork->unk_0B == 0 && func_801F04A4() == 0) {
        BATTLE_RAISE_STATE(BATTLE_STATE_EFFECT_PLAYING);
        func_801E5988();
    }
}

MATCH void func_801EEFB0(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

MATCH void func_801EEFF4(void) {
    BmagicEffectFuncs handlers;

    BMAGIC_DISPATCH_STEP_HANDLERS(D_801EEC04, unk_02);
}

INCLUDE_ASM(func_801EF06C);

INCLUDE_ASM(func_801EF2DC);

INCLUDE_ASM(func_801EF3D4);

/* func_801EF4E4 */
#include "overlays/bmagic/Effect_NextStepUnderTickLimit.h"

INCLUDE_ASM(func_801EF52C);

INCLUDE_ASM(func_801EF6B8);

MATCH void func_801EF724(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectFuncs + 1), 1, D_801F21F0);
}

INCLUDE_ASM(func_801EF768);

INCLUDE_ASM(func_801EF864);

INCLUDE_ASM(func_801EFA64);

MATCH void func_801EFB14(void) {
    u16 phase;
    u8  timer;

    BMAGIC_SWAY_EFFECT_WORK(D_801F21F0, func_801F0454)
}

INCLUDE_ASM(func_801EFBF8);

INCLUDE_ASM(func_801EFE2C);

INCLUDE_ASM(func_801F00C4);

INCLUDE_ASM(func_801F03E8);

MATCH void func_801F0454(void) {
    D_801F21F0->flags_00 = 0;
    D_801F21F0->step_01  = 0;
    D_801F21F0->unk_02   = 0;
    D_801F21F0->unk_03   = 0;
    D_801F21F0->unk_04   = 0;
}

INCLUDE_ASM(func_801F04A4);

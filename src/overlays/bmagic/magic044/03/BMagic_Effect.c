#include "magic044_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    Bmagic_DispatchTaskPair(func_801EEC5C, func_801EEDA0);
}

INCLUDE_ASM(func_801EEC5C);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EEE00(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

INCLUDE_ASM(func_801EEE44);

INCLUDE_ASM(func_801EEEFC);

INCLUDE_ASM(func_801EF138);

INCLUDE_ASM(func_801EF320);

MATCH void func_801EF478(void) {
    u8 timer;

    func_801F0390();
    timer              = g_SpadWork->unk_09 - 1;
    g_SpadWork->unk_09 = timer;
    if (timer == 0) {
        BMAGIC_TICK_EFFECT_WORK();
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF4E0);

INCLUDE_ASM(func_801EFA4C);

MATCH void func_801F02A0(void) {
    s32 i;

    BMAGIC_SHIFT_TRAIL(D_801F0A38)
    D_801F0A38[g_SpadWork->unk_04][g_SpadWork->unk_0B].x = g_SpadWork->unk_2E.half;
    D_801F0A38[g_SpadWork->unk_04][g_SpadWork->unk_0B].y = g_SpadWork->unk_30.half;
}

MATCH void func_801F0390(void) {
    s32 i;

    BMAGIC_SHIFT_TRAIL(D_801F0A38)
    D_801F0A38[g_SpadWork->unk_04][g_SpadWork->unk_0B].x = -1;
    D_801F0A38[g_SpadWork->unk_04][g_SpadWork->unk_0B].y = -1;
}

MATCH void func_801F0478(void) {
    SYS_DISPATCH_BYTE(D_801F0A2C, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        func_801F06D8();
    }
}

INCLUDE_ASM(func_801F04F0);

INCLUDE_ASM(func_801F05AC);

INCLUDE_ASM(func_801F0638);

INCLUDE_ASM(func_801F06D8);

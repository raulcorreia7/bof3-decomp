#include "magic169_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC38);

INCLUDE_ASM(func_801EED8C);

INCLUDE_ASM(func_801EEEB0);

MATCH void func_801EEFE0(void) {
    u8 timer;

    if (g_SpadWork->word_08.byte.unk_0B == 0) {
        timer                           = g_SpadWork->word_08.byte.unk_09 - 1;
        g_SpadWork->word_08.byte.unk_09 = timer;
        if (!(timer & 0xFF)) {
            g_SpadWork->step_01 += 1;
        }
    }
}

#include "shared/Effect_StartPlaying.h"

INCLUDE_ASM(func_801EF070);

MATCH void func_801EF210(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

MATCH void func_801EF254(void) {
    BmagicEffectFuncs handlers;

    BMAGIC_DISPATCH_STEP_HANDLERS(D_801EEC14, unk_02);
}

INCLUDE_ASM(func_801EF2CC);

INCLUDE_ASM(func_801EF444);

INCLUDE_ASM(func_801EF4FC);

#include "overlays/bmagic/Effect_NextStepUnderTickLimit.h"

INCLUDE_ASM(func_801EF688);

MATCH void func_801EF7D0(void) {
    if (g_SpadWork->word_08.byte.unk_0B == 0) {
        BATTLE_ACTIVE_WORK->word_08.byte.unk_0B -= 1;
        if (func_801DB524(g_SpadWork->unk_04) & 0xFF) {
            func_800A9820(g_SpadWork->unk_04);
        }
        func_801E5988();
    }
}

MATCH void func_801EF860(void) {
    SYS_DISPATCH_TASK(D_801F0420, 1, g_SpadWork);
}

INCLUDE_ASM(func_801EF8A4);

INCLUDE_ASM(func_801EFA18);

INCLUDE_ASM(func_801EFBC4);

INCLUDE_ASM(func_801EFCF4);

INCLUDE_ASM(func_801EFE3C);

INCLUDE_ASM(func_801F0090);

/* func_801F0368 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801F03CC */
MATCH void Actor_Clear(void) {
    Bmagic_ResetLocalWork();
}

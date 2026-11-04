#include "magic076_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC28);

INCLUDE_ASM(func_801EED48);

INCLUDE_ASM(func_801EEF5C);

INCLUDE_ASM(func_801EF00C);

/* func_801EF11C */
#include "overlays/bmagic/Effect_NextStep.h"

INCLUDE_ASM(func_801EF160);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

INCLUDE_ASM(func_801EF2E8);

MATCH void func_801EF330(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

MATCH void func_801EF374(void) {
    SYS_DISPATCH_BYTE(D_801F048C, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        func_800AF764();
        func_801EF698();
    }
}

INCLUDE_ASM(func_801EF3F4);

INCLUDE_ASM(func_801EF4A8);

#include "overlays/bmagic/Effect_CountDownAndStep.h"

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

INCLUDE_ASM(func_801EF698);

MATCH void func_801EF8A8(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectFuncs + 6), 1, g_SpadWork);
}

INCLUDE_ASM(func_801EF8EC);

INCLUDE_ASM(func_801EFA60);

INCLUDE_ASM(func_801EFC30);

INCLUDE_ASM(func_801EFD60);

INCLUDE_ASM(func_801EFEA8);

INCLUDE_ASM(func_801F00FC);

/* func_801F03D4 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801F0438 */
MATCH void Actor_Clear(void) {
    Bmagic_ResetLocalWork();
}

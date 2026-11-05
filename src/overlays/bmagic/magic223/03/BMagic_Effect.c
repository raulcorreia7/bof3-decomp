#include "magic223_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC10);

INCLUDE_ASM(func_801EED18);

#include "overlays/bmagic/Effect_RequestTargetOnTimerZero.h"

/* Best 3 differences: address load at 0x801EEFC8; adjust flags pointer placement. */
INCLUDE_ASM(func_801EEFB4);

MATCH void func_801EF00C(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

MATCH void func_801EF050(void) {
    SYS_DISPATCH_TASK(g_BMagicEffectFuncs + 1, 2, g_SpadWork);
    if (g_SpadWork->flags_00 != 0) {
        func_801EF1E8();
    }
}

#include "overlays/bmagic/Effect_ArmCounterNextStep.h"

#include "overlays/bmagic/Effect_CountUpAndStep.h"

#include "overlays/bmagic/Effect_StepWhileTickUnderTwo.h"

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

INCLUDE_ASM(func_801EF1E8);

MATCH void func_801EF3C0(void) {
    SYS_DISPATCH_TASK(D_801EFC40, 1, g_SpadWork);
}

MATCH void func_801EF404(void) {
    SYS_DISPATCH_BYTE(D_801EFC44, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        func_801EF7A8();
    }
}

INCLUDE_ASM(func_801EF47C);

INCLUDE_ASM(func_801EF628);

INCLUDE_ASM(func_801EF6E0);

INCLUDE_ASM(func_801EF7A8);

/* func_801EFB78 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801EFBDC */
MATCH void Actor_Clear(void) {
    Bmagic_ResetLocalWork();
}

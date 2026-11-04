#include "magic129_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC10);

INCLUDE_ASM(func_801EED18);

#include "overlays/bmagic/Effect_RequestTargetOnTimerZero.h"

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EEF80(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

INCLUDE_ASM(func_801EEFC4);

INCLUDE_ASM(func_801EF058);

INCLUDE_ASM(func_801EF38C);

INCLUDE_ASM(func_801EF3DC);

INCLUDE_ASM(func_801EF4F0);

INCLUDE_ASM(func_801EF54C);

MATCH void func_801EFF40(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectFuncs + 5), 1, g_SpadWork);
}

INCLUDE_ASM(func_801EFF84);

INCLUDE_ASM(func_801F00D4);

INCLUDE_ASM(func_801F023C);

INCLUDE_ASM(func_801F029C);

INCLUDE_ASM(func_801F030C);

/* func_801F0500 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801F0564 */
MATCH void Actor_Clear(void) {
    Bmagic_ResetLocalWork();
}

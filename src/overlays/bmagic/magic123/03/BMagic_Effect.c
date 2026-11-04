#include "magic123_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC04);

INCLUDE_ASM(func_801EEDAC);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EF0C4(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

MATCH void func_801EF108(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectFuncs + 2), 2, g_SpadWork);
}

INCLUDE_ASM(func_801EF14C);

INCLUDE_ASM(func_801EF28C);

INCLUDE_ASM(func_801EF4AC);

MATCH void func_801EF550(void) {
    BATTLE_ACTIVE_WORK->unk_0B--;
    Actor_Clear();
}

INCLUDE_ASM(func_801EF584);

INCLUDE_ASM(func_801EF750);

INCLUDE_ASM(func_801EF9E0);

/* func_801EFCA0 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801EFD04 */
MATCH void Actor_Clear(void) {
    Bmagic_ResetLocalWork();
}

#include "magic213_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC04);

INCLUDE_ASM(func_801EED04);

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

MATCH void func_801EEFC0(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

MATCH void func_801EF004(void) {
    SYS_DISPATCH_TASK(D_801EF8A4, 2, g_SpadWork);
}

INCLUDE_ASM(func_801EF048);

INCLUDE_ASM(func_801EF23C);

INCLUDE_ASM(func_801EF348);

#include "overlays/bmagic/Effect_TickOnZeroTick.h"

MATCH void func_801EF4E0(void) {
    SYS_DISPATCH_TASK(D_801EF8B4, 1, g_SpadWork);
}

INCLUDE_ASM(func_801EF524);

INCLUDE_ASM(func_801EF5BC);

MATCH void func_801EF7A0(void) {
    PartyBattler* work;

    if (func_8014DAEC() != 0u) {
        work         = (PartyBattler*)D_801EB4E0;
        work->unk_0B = work->unk_0B - 1;
        Actor_Clear();
    }
}

/* func_801EF7EC */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801EF850 */
MATCH void Actor_Clear(void) {
    Bmagic_ResetLocalWork();
}

#include "magic115_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC14.h"

INCLUDE_ASM(func_801EEC80);

INCLUDE_ASM(func_801EEDDC);

INCLUDE_ASM(func_801EEEB0);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EF054(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

INCLUDE_ASM(func_801EF098);

INCLUDE_ASM(func_801EF130);

INCLUDE_ASM(func_801EF27C);

INCLUDE_ASM(func_801EF49C);

#include "overlays/bmagic/Effect_TickDownAndClear.h"

INCLUDE_ASM(func_801EF5F8);

INCLUDE_ASM(func_801EF690);

MATCH void func_801EF7A4(void) {
    func_8014DAEC();
    if (func_8014DAEC() != 0u) {
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 2;
    }
}

INCLUDE_ASM(func_801EF7F4);

MATCH void Effect_TickDownAndClear_801EF888(void) {
    EFFECT_TICK_DOWN_AND_CLEAR();
}

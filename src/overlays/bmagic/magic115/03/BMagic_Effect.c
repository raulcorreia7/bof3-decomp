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
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_SpadWork->step_01);
}

INCLUDE_ASM(func_801EF098);

/* First difference: lui a0 at +0x50; try the work pointer lifetime after the depth copy. */
INCLUDE_ASM(func_801EF130);

INCLUDE_ASM(func_801EF27C);

INCLUDE_ASM(func_801EF49C);

#include "overlays/bmagic/Effect_TickDownAndClear.h"

INCLUDE_ASM(func_801EF5F8);

MATCH void func_801EF690(void) {
    g_SpadWork->unk_25      = 0x1D;
    g_SpadWork->unk_26      = 0;
    g_SpadWork->unk_40      = 0x10000;
    g_SpadWork->unk_44      = 0x10000;
    g_SpadWork->unk_48      = 1;
    g_SpadWork->unk_27      = 0xA0;
    g_SpadWork->unk_28      = 0;
    g_SpadWork->unk_24      = 4;
    g_SpadWork->unk_5D      = 0;
    g_SpadWork->unk_5E      = 0;
    g_SpadWork->unk_5F      = 0;
    g_SpadWork->unk_5C      = 0;
    g_SpadWork->unk_2A      = 0;
    g_SpadWork->unk_29      = 4;
    g_SpadWork->unk_2C.half = 0;
    g_SpadWork->unk_2B      = 0;
    Actor_SelectScript(1U);
    g_SpadWork->unk_02 += 1;
}

MATCH void func_801EF7A4(void) {
    func_8014DAEC();
    if (func_8014DAEC() != 0u) {
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 2;
    }
}

MATCH void func_801EF7F4(void) {
    s32 value = -0x80;
    g_SpadWork->unk_5D -= 4;
    g_SpadWork->unk_5E -= 4;
    g_SpadWork->unk_5F -= 4;
    func_8014DAEC();
    g_SpadWork->unk_5D = value;
    g_SpadWork->unk_02 += 1;
}

MATCH void Effect_TickDownAndClear_801EF888(void) {
    EFFECT_TICK_DOWN_AND_CLEAR();
}

#include "magic048_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_RunStep.h"

INCLUDE_ASM(func_801EEC70);

#include "overlays/bmagic/Effect_CountDownTimerQueueFx.h"

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EEE70(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

MATCH void func_801EEEB4(void) {
    SYS_DISPATCH_BYTE(D_801EF81C, g_SpadWork->unk_02);
    if (g_SpadWork->unk_02 != 0 && g_SpadWork->flags_00 != 0) {
        func_801EF5C8();
        func_801EF234();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EEF3C);

INCLUDE_ASM(func_801EF05C);

INCLUDE_ASM(func_801EF158);

INCLUDE_ASM(func_801EF234);

INCLUDE_ASM(func_801EF5C8);

INCLUDE_ASM(func_801EF6A0);

#include "magic143_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    Callback handlers[2] = {func_801EEC5C, func_801EED24};

    SYS_DISPATCH_TASK(handlers, 1, g_Task);
}

INCLUDE_ASM(func_801EEC5C);

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

MATCH void func_801EED70(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectModes, g_Task->header.mode);
}

INCLUDE_ASM(func_801EEDB4);

MATCH void func_801EEF10(void) {
    g_Task->param.unk_0B = RANDOM_MASK(15);
    g_Task->unk_09       = 0;
    g_Task->timer        = 0;
    g_Task->header.step++;
}

INCLUDE_ASM(func_801EEF78);

INCLUDE_ASM(func_801EF054);

#include "overlays/bmagic/Effect_CountDownByTwoAndFinish.h"

#include "overlays/bmagic/Effect_SetActorMatrixRolled.h"

INCLUDE_ASM(func_801EF23C);

/* blocker: base length 128 against 64; first diff: li v0,64 against li v0,128 at +0x18. */
INCLUDE_ASM(func_801EF9A4);

INCLUDE_ASM(func_801EFC74);

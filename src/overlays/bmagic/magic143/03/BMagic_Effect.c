#include "magic143_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    Callback handlers[2] = {func_801EEC5C, func_801EED24};

    SYS_DISPATCH_TASK(handlers, 1, g_SpadWork);
}

INCLUDE_ASM(func_801EEC5C);

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

MATCH void func_801EED70(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_SpadWork->step_01);
}

INCLUDE_ASM(func_801EEDB4);

MATCH void func_801EEF10(void) {
    g_SpadWork->word_08.byte.unk_0B   = rand() & 15;
    g_SpadWork->word_08.byte.unk_09   = 0;
    g_SpadWork->word_08.byte.timer_0A = 0;
    g_SpadWork->unk_02++;
}

INCLUDE_ASM(func_801EEF78);

INCLUDE_ASM(func_801EF054);

#include "overlays/bmagic/Effect_CountDownByTwoAndFinish.h"

#include "overlays/bmagic/Effect_SetActorMatrixRolled.h"

INCLUDE_ASM(func_801EF23C);

/* Follows sce10eff func_801D218C (160 instructions) but draws through Area_AddCellPrim(x, y, 2, 12) and starts with a
 * 128 base length where the template has 64 (first difference li v0,64 against li v0,128 at +0x18; the frame is also 64
 * bytes against 56). */
INCLUDE_ASM(func_801EF9A4);

INCLUDE_ASM(func_801EFC74);

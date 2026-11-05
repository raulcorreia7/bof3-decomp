#include "magic097_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    Bmagic_DispatchTaskPair(func_801EEC5C, func_801EEF38);
}

INCLUDE_ASM(func_801EEC5C);

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

MATCH void func_801EEF84(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

INCLUDE_ASM(func_801EEFC8);

MATCH void func_801EF114(void) {
    u8 counter;

    counter                         = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = counter;
    if (!(counter & 0xFF)) {
        g_SpadWork->word_08.byte.unk_0B   = rand() & 0xF;
        g_SpadWork->word_08.byte.unk_09   = 0;
        g_SpadWork->word_08.byte.timer_0A = 0;
        g_SpadWork->unk_02 += 1;
    }
}

INCLUDE_ASM(func_801EF1A4);

INCLUDE_ASM(func_801EF324);

#include "overlays/bmagic/Effect_CountDownByTwoAndFinish.h"

#include "overlays/bmagic/Effect_SetActorMatrixRolled.h"

INCLUDE_ASM(func_801EF5C4);

INCLUDE_ASM(func_801EFE04);

/* Follows sce10eff func_801D218C (160 instructions) but draws through Area_AddCellPrim(x, y, 2, 12) with the vector
 * scaled by sra 3 into the call, so the frame is 64 bytes against 56 (first difference addiu sp at +0x0) */
INCLUDE_ASM(func_801F0568);

INCLUDE_ASM(func_801F083C);

#include "magic098_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    BMagic_DispatchTaskPair(func_801EEC5C, func_801EEF38);
}

INCLUDE_ASM(func_801EEC5C);

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

/* func_801EEF84 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEFC8(void) {
    SYS_DISPATCH_BYTE((g_BMagicEffectModes + 1), g_Task->header.step);
    func_800AF764();
    if (g_Task->header.step != 0 && g_Task->header.flags != 0) {
        Effect_SetActorMatrixRolled();
        func_801EF5D4(24, 32, 3);
        g_Task->param.unk_0B += 8;
        func_801EF5D4(16, 80, 0xF);
        g_Task->param.unk_0B += 2;
        func_801EFE24();
        g_Task->param.unk_0B += 6;
        func_801EF5D4(16, 128, 0x1F);
        g_Task->param.unk_0B -= 16;
        g_Task->unk_2E.half += 24;
        func_801F00C4();
        g_Task->unk_2E.half -= 48;
        func_801F00C4();
        PopMatrix();
    }
}

#include "overlays/bmagic/Effect_CountDownAndPickRandom.h"

INCLUDE_ASM(func_801EF1B4);

/* func_801EF334 */
#include "overlays/bmagic/Effect_ReleaseTarget.h"

#include "overlays/bmagic/Effect_CountDownByTwoAndFinish.h"

#include "overlays/bmagic/Effect_SetActorMatrixRolled.h"

INCLUDE_ASM(func_801EF5D4);

INCLUDE_ASM(func_801EFE24);

INCLUDE_ASM(func_801F00C4);

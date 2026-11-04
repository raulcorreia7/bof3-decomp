#include "magic009_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC28.h"

INCLUDE_ASM(func_801EEC98);

INCLUDE_ASM(func_801EEF08);

#include "overlays/bmagic/Effect_CountDownTimerNextStep.h"

#include "overlays/bmagic/Effect_NextStepOnWorkZeroTick.h"

/* Pointer and saved-target forms: first difference is lui v1 at 0x801EF0A0. */
INCLUDE_ASM(func_801EF09C);

MATCH void func_801EF0DC(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

MATCH void func_801EF120(void) {
    SYS_DISPATCH_BYTE(D_801EF8A4, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        func_801EF3B8();
    }
}

INCLUDE_ASM(func_801EF198);

#include "overlays/bmagic/Effect_CountUpTimersByTwoNextStep.h"

#include "overlays/bmagic/Effect_CountDownTimer.h"

INCLUDE_ASM(func_801EF3B8);

INCLUDE_ASM(func_801EF6B0);

#include "overlays/bmagic/Effect_ReloadTimerAndStep.h"

INCLUDE_ASM(func_801EF788);

INCLUDE_ASM(func_801EF814);

MATCH void func_801EF87C(void) {
    func_801E5988();
}

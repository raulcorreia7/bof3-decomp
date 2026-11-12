#include "magic145_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_DispatchMode.h"

INCLUDE_ASM(func_801EEC70);

#include "overlays/bmagic/Effect_NextStepOnZeroTick.h"

#include "shared/Effect_PlayOnce.h"

/* func_801EEE2C */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEE70(void) {
    SYS_DISPATCH_BYTE(D_801EF418, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_DrawTexturedQuad();
    }
}

INCLUDE_ASM(func_801EEEE8);

#include "overlays/bmagic/Effect_CountUpTimersByTwoNextStep.h"

/* func_801EF0A0 */
MATCH void Effect_CountDownTimer(void) {
    BMagic_CountDownEffectTimer(1);
}

#include "overlays/bmagic/Effect_DrawTexturedQuad.h"

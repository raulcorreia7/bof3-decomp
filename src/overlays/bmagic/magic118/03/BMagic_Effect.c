#include "magic118_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC18(void) {
    BattleHandlerTable5 handlers;

    handlers = D_801EEC04;
    SYS_DISPATCH_BYTE(handlers.handlers, g_Task->mode);
    if (g_Task->flags != 0 && g_Task->mode != 0) {
        Effect_SetActorMatrix();
        func_801EF6BC();
        func_801EFA1C();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EECD4);

MATCH void func_801EEE20(void) {
    u8 timer;

    timer          = g_Task->unk_09 + 1;
    g_Task->unk_09 = timer;
    if (timer == 16) {
        func_800A9610(g_BattleTargetSelector, 0x10);
        g_Task->mode = g_Task->mode + 1;
    }
}

#include "overlays/bmagic/Effect_NextStepOnWorkLastTick.h"

#include "overlays/bmagic/Effect_CountDownTimerNextStep.h"

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EEF6C(void) {
    SYS_DISPATCH_BYTE(D_801EFCD4, g_Task->mode);
    if (g_Task->flags != 0 && g_Task->mode != 0) {
        Effect_SetActorMatrix();
        func_801EF194();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EEFF4);

/* blocker: sum register; first diff: lw a0,0x20($v1) (retail) against lw v0,0x20($v1). */
INCLUDE_ASM(func_801EF0A4);

INCLUDE_ASM(func_801EF108);

INCLUDE_ASM(func_801EF194);

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801EF6BC);

INCLUDE_ASM(func_801EFA1C);

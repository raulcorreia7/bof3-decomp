#include "magic118_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* func_801EEC18 */
MATCH void BMagic_UpdateBurn(void) {
    BattleHandlerTable5 handlers;

    handlers = D_801EEC04;
    SYS_DISPATCH_BYTE(handlers.handlers, g_Task->header.mode);
    if (g_Task->header.flags != 0 && g_Task->header.mode != 0) {
        Effect_SetActorMatrix();
        BMagic_DrawBurnFlameQuads();
        BMagic_DrawBurnFlameTris();
        PopMatrix();
    }
}

INCLUDE_ASM(BMagic_SpawnBurnFlames);

/* func_801EEE20 */
MATCH void BMagic_SelectBurnTarget(void) {
    u8 timer;

    timer          = g_Task->unk_09 + 1;
    g_Task->unk_09 = timer;
    if (timer == 16) {
        func_800A9610(g_BattleTargetSelector, 0x10);
        g_Task->header.mode = g_Task->header.mode + 1;
    }
}

#include "overlays/bmagic/Effect_NextStepOnWorkLastTick.h"

#include "overlays/bmagic/Effect_CountDownTimerNextStep.h"

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EEF6C */
MATCH void BMagic_UpdateBurnSprites(void) {
    SYS_DISPATCH_BYTE(D_801EFCD4, g_Task->header.mode);
    if (g_Task->header.flags != 0 && g_Task->header.mode != 0) {
        Effect_SetActorMatrix();
        BMagic_DrawBurnSprites();
        PopMatrix();
    }
}

/* Retail keeps the battler in v1 and the task in a0; the draft (--dec form, timer 2, unk_14 zero) is one instruction short at the 0x14 bnez, the reg order differs. */
INCLUDE_ASM(func_801EEFF4);

/* blocker: sum register; first diff: lw a0,0x20($v1) (retail) against lw v0,0x20($v1). */
/* blocker: timer and unk_20 load order; first diff: lbu a1 against v0 at 0x801EF0B0. */
INCLUDE_ASM(func_801EF0A4);

MATCH void func_801EF108(void) {
    PartyBattler* work;
    u8            timer;

    g_Task->param.unk_0B--;
    work         = g_Task;
    timer        = work->unk_09 - 1;
    work->unk_09 = timer;
    work->unk_20 += work->timer;
    work->unk_14 += work->unk_20;
    if (timer == 0) {
        g_BattleEffectBattler->param.unk_0B--;
        func_801E5988();
    }
}

INCLUDE_ASM(BMagic_DrawBurnSprites);

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(BMagic_DrawBurnFlameQuads);

INCLUDE_ASM(BMagic_DrawBurnFlameTris);

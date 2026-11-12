#include "magic146_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC10(void) {
    Magic146Steps handlers = D_801EEC04;
    PartyMember*  saved_task;
    PartyMember*  saved_battler;
    u8            i;

    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.mode);

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        if (D_801EF9F4[i].header.flags & BMAGIC_EFFECT_IN_USE) {
            saved_task            = g_Task;
            saved_battler         = g_BattleEffectBattler;
            g_Task                = (PartyMember*)&D_801EF9F4[i];
            g_BattleEffectBattler = D_801EF9F4[i].target.party;
            func_801EF2FC();
            g_BattleEffectBattler = saved_battler;
            g_Task                = saved_task;
        }
    }
}

INCLUDE_ASM(func_801EED18);

#include "overlays/bmagic/Effect_NextStepOnZeroTick.h"

#include "shared/Effect_PlayOnce.h"

/* func_801EF04C */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF090(void) {
    SYS_DISPATCH_TASK(D_801EF9B8, 2, g_Task);
}

INCLUDE_ASM(func_801EF0D4);

#include "overlays/bmagic/Effect_FinishOnZeroTick.h"

MATCH void func_801EF2FC(void) {
    SYS_DISPATCH_TASK(D_801EF9C0, 1, g_Task);
}

MATCH void func_801EF340(void) {
    SYS_DISPATCH_BYTE(D_801EF9C4, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_DrawTexturedQuad();
    }
}

INCLUDE_ASM(func_801EF3B8);

#include "overlays/bmagic/Effect_CountUpTimersByTwoNextStep.h"

MATCH void func_801EF58C(void) {
    PartyMember* work;
    PartyMember* active;
    u8           count;

    work = g_Task;
    work->unk_09++;
    work        = g_Task;
    count       = work->timer - 1;
    work->timer = count;
    if (count == 0) {
        active = BATTLE_ACTIVE_WORK;
        active->param.unk_0B--;
        Actor_Clear();
    }
}

#include "overlays/bmagic/Effect_DrawTexturedQuad.h"

/* func_801EF900 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801EF964 */
#include "overlays/bmagic/Actor_Clear.h"

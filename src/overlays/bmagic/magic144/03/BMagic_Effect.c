#include "magic144_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    PartyMember* saved_task;
    PartyMember* saved_battler;
    u8           i;

    BMagic_DispatchTaskPair(func_801EED04, Effect_StartOnZeroTick);

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        if (D_801F050C[i].header.flags & BMAGIC_EFFECT_IN_USE) {
            saved_task            = g_Task;
            saved_battler         = g_BattleEffectBattler;
            g_Task                = (PartyMember*)&D_801F050C[i];
            g_BattleEffectBattler = D_801F050C[i].target.party;
            func_801EF510();
            g_BattleEffectBattler = saved_battler;
            g_Task                = saved_task;
        }
    }
}

INCLUDE_ASM(func_801EED04);

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

MATCH void func_801EEE9C(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectModes, TASK_BYTES[1]);
}

MATCH void func_801EEEE0(void) {
    SYS_DISPATCH_BYTE(D_801F04D4, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        func_801EF294();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EEF68);

MATCH void func_801EF078(void) {
    u8            timer;
    PartyMember** actor;
    timer          = g_Task->unk_09 + 2;
    g_Task->unk_09 = timer;
    if (timer == 0x10) {
        actor = &g_Battle.selected_actor;
        GFX_FreePaletteFadeTarget(*actor);
        GFX_AllocPaletteFade(*actor, -8, -8, -8, 1);
        func_800A9820(g_Battle.target_selector);
        g_Task->header.step += 1;
    }
}

#include "overlays/bmagic/Effect_StepOnOwnTickFlag.h"

MATCH void func_801EF154(void) {
    u8 count;

    count = g_Task->unk_09;
    if (count != 0) {
        g_Task->unk_09 = count - 1;
    }
    if (g_Task->param.unk_0B == 0x80) {
        GFX_FreePaletteFadeTarget(g_Battle.selected_actor);
        func_800AF814(g_Battle.target_selector);
        BATTLE_ACTIVE_WORK->param.unk_0B -= 1;
        func_801E5988();
    }
}

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801EF294);

MATCH void func_801EF510(void) {
    SYS_DISPATCH_TASK(D_801F04E4, 1, g_Task);
}

MATCH void func_801EF554(void) {
    SYS_DISPATCH_BYTE(D_801F04EC, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_800AF764();
        func_801EF818();
    }
}

#include "overlays/bmagic/Effect_StartAtTarget.h"

MATCH void func_801EF654(void) {
    EFFECT_ADVANCE_AT_COUNT(4, 0x11);
}

#include "overlays/bmagic/Effect_CountUpAndMarkBattler.h"

#include "overlays/bmagic/Effect_CountDownByTwoFinishAtOne.h"

INCLUDE_ASM(func_801EF818);

/* hint: first differing instruction is the flags beqz at +0x48 (candidate four instructions longer): retail loads unk_30 inside each arm of the param.unk_0B == 1 test, the candidate loads it after the if. */
INCLUDE_ASM(func_801EFF74);

#include "overlays/bmagic/Effect_AppearAtTarget.h"

MATCH void func_801F00A0(void) {
    EFFECT_ADVANCE_AT_COUNT(2, 0x10);
}

#include "overlays/bmagic/Effect_StepOnTickFlag.h"

#include "overlays/bmagic/Effect_CountDownCounterAndFinish.h"

INCLUDE_ASM(func_801F01D0);

/* func_801F046C */
#include "overlays/bmagic/BMagic_AllocEffect.h"

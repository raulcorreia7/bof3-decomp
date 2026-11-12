#include "magic092_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    PartyMember* saved_task;
    PartyMember* saved_battler;
    u8           i;

    BMagic_DispatchTaskPair(func_801EED04, Effect_StartOnZeroTick);

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        if (D_801F07F8[i].header.flags & BMAGIC_EFFECT_IN_USE) {
            saved_task            = g_Task;
            saved_battler         = g_BattleEffectBattler;
            g_Task                = (PartyMember*)&D_801F07F8[i];
            g_BattleEffectBattler = D_801F07F8[i].target.party;
            func_801EF7FC();
            g_BattleEffectBattler = saved_battler;
            g_Task                = saved_task;
        }
    }
}

INCLUDE_ASM(func_801EED04);

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

/* func_801EF000 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF044(void) {
    SYS_DISPATCH_BYTE(D_801F07C0, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        func_801EF580();
        PopMatrix();
    }
}

MATCH void func_801EF0CC(void) {
    PartyMember* work;
    u8           count;
    u8           i;
    u8           slot;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (count == 0) {
        g_Task->param.unk_0B = 0;
        for (i = 0; i < 3; i++) {
            slot = BMagic_AllocEffect();
            if (slot != GAME_NONE) {
                work                                  = g_Task;
                BMAGIC_EFFECT_SLOTS[slot].header.mode = i != 0;
                BMAGIC_EFFECT_SLOTS[slot].header.step = 0;
                BMAGIC_EFFECT_SLOTS[slot].unk_0B      = i;
                BMAGIC_EFFECT_SLOTS[slot].header.flags |= BMAGIC_EFFECT_IN_USE | ACTOR_FLAG_HIDDEN;
                BMAGIC_EFFECT_SLOTS[slot].target.party = work;
                g_Task->param.unk_0B += 1;
            }
        }
        SND_QueueSelectionFx(EMI_CUE_ID(SND_BANK_COMMON, 0x00));
        g_Task->header.step += 1;
    }
}

INCLUDE_ASM(func_801EF1F0);

#include "overlays/bmagic/Effect_StepOnOwnTickFlag.h"

MATCH void func_801EF388(void) {
    u8 count;

    count = g_Task->unk_09;
    if (count != 0) {
        g_Task->unk_09 = count - 1;
    }
    if (g_Task->param.unk_0B == 0x80) {
        if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
            GFX_FreePaletteFadeTarget(&g_BattleEnemyBattlers[g_Task->unk_03]);
            func_800AF814((g_Task->unk_03 + 3) & BYTE_MASK);
            Battle_MarkDamaged((g_Task->unk_03 + 3) & BYTE_MASK);
        } else {
            GFX_FreePaletteFadeTarget((EnemyBattler*)&g_Game.members[g_Task->unk_03]);
            func_800AF814(g_Task->unk_03);
            Battle_MarkDamaged(g_Task->unk_03);
        }
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801E5988();
    }
}

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801EF580);

MATCH void func_801EF7FC(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 5), 1, g_Task);
}

MATCH void func_801EF840(void) {
    SYS_DISPATCH_BYTE(D_801F07D8, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Battle_ProjectRange();
        func_801EFB04();
    }
}

#include "overlays/bmagic/Effect_StartAtTarget.h"

MATCH void func_801EF940(void) {
    EFFECT_ADVANCE_AT_COUNT(4, 0x11);
}

#include "overlays/bmagic/Effect_CountUpAndMarkBattler.h"

#include "overlays/bmagic/Effect_CountDownByTwoFinishAtOne.h"

INCLUDE_ASM(func_801EFB04);

MATCH void func_801F0260(void) {
    PartyMember* work;
    u16          x;
    u16          y;

    SYS_DISPATCH_BYTE(D_801F07E8, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Battle_ProjectRange();
        work = g_Task;
        if (work->param.unk_0B == 1) {
            x = work->unk_2E.half - MAGIC092_STEP_X;
            y = work->unk_30.half;
        } else {
            x = work->unk_2E.half + MAGIC092_STEP_X;
            y = work->unk_30.half;
        }
        y -= MAGIC092_RISE_Y;
        work->unk_2E.half = x;
        work->unk_30.half = y;
        func_801F04BC();
    }
}

#include "overlays/bmagic/Effect_AppearAtTarget.h"

MATCH void func_801F038C(void) {
    EFFECT_ADVANCE_AT_COUNT(2, 0x10);
}

#include "overlays/bmagic/Effect_StepOnTickFlag.h"

#include "overlays/bmagic/Effect_CountDownCounterAndFinish.h"

INCLUDE_ASM(func_801F04BC);

/* func_801F0758 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

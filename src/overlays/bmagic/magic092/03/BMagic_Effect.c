#include "magic092_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    PartyBattler* saved_task;
    PartyBattler* saved_battler;
    u8            i;

    BMagic_DispatchTaskPair(func_801EED04, Effect_StartOnZeroTick);

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        if (D_801F07F8[i].header.flags & BMAGIC_EFFECT_IN_USE) {
            saved_task            = g_Task;
            saved_battler         = g_BattleEffectBattler;
            g_Task                = (PartyBattler*)&D_801F07F8[i];
            g_BattleEffectBattler = D_801F07F8[i].target.party;
            func_801EF7FC();
            g_BattleEffectBattler = saved_battler;
            g_Task                = saved_task;
        }
    }
}

INCLUDE_ASM(func_801EED04);

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

MATCH void func_801EF000(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectModes, g_Task->header.mode);
}

MATCH void func_801EF044(void) {
    SYS_DISPATCH_BYTE(D_801F07C0, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        func_801EF580();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EF0CC);

// hint: same shape as magic093 801EF108 and magic097 801EF1A4 (retail 4 bytes longer: v1 index, base added last); enemy-table forms tried do not match
INCLUDE_ASM(func_801EF1F0);

#include "overlays/bmagic/Effect_StepOnOwnTickFlag.h"

MATCH void func_801EF388(void) {
    u8 count;

    count = g_Task->unk_09;
    if (count != 0) {
        g_Task->unk_09 = count - 1;
    }
    if (g_Task->param.unk_0B == 0x80) {
        if (g_BattleTargetSelector & BATTLE_TARGET_ENEMY_SIDE) {
            GFX_FreePaletteFadeTarget(&g_BattleEnemyBattlers[g_Task->unk_03]);
            func_800AF814((g_Task->unk_03 + 3) & BYTE_MASK);
            func_800A9820((g_Task->unk_03 + 3) & BYTE_MASK);
        } else {
            GFX_FreePaletteFadeTarget((EnemyBattler*)&g_BattlePartyBattlers[g_Task->unk_03]);
            func_800AF814(g_Task->unk_03);
            func_800A9820(g_Task->unk_03);
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
        func_800AF764();
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

INCLUDE_ASM(func_801F0260);

#include "overlays/bmagic/Effect_AppearAtTarget.h"

MATCH void func_801F038C(void) {
    EFFECT_ADVANCE_AT_COUNT(2, 0x10);
}

#include "overlays/bmagic/Effect_StepOnTickFlag.h"

#include "overlays/bmagic/Effect_CountDownCounterAndFinish.h"

INCLUDE_ASM(func_801F04BC);

/* func_801F0758 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

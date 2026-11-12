#include "magic223_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/Effect_RunSlots.h"

INCLUDE_ASM(func_801EED18);

#include "overlays/bmagic/Effect_RequestTargetOnTimerZero.h"

/* When the effect ticker is zero, marks the hit applied and the effect playing, tells the battle UI and
 * runs the effect player's follow-up. */
MATCH void func_801EEFB4(void) {
    u16* flags;

    if (g_Task->param.unk_0B == 0) {
        BATTLE_RAISE_STATE(BATTLE_STATE_DAMAGE_APPLIED | BATTLE_STATE_EFFECT_PLAYING);
        func_800A9820(g_Battle.target_selector);
        func_801E5988();
    }
}

/* func_801EF00C */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF050(void) {
    SYS_DISPATCH_TASK(g_BMagicEffectModes + 1, 2, g_Task);
    if (g_Task->header.flags != 0) {
        func_801EF1E8();
    }
}

#include "overlays/bmagic/Effect_ArmCounterNextStep.h"

#include "overlays/bmagic/Effect_CountUpAndStep.h"

#include "overlays/bmagic/Effect_StepWhileTickUnderTwo.h"

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

INCLUDE_ASM(func_801EF1E8);

MATCH void func_801EF3C0(void) {
    SYS_DISPATCH_TASK(D_801EFC40, 1, g_Task);
}

MATCH void func_801EF404(void) {
    SYS_DISPATCH_BYTE(D_801EFC44, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_801EF7A8();
    }
}

MATCH void func_801EF47C(void) {
    s32* angle_cell;
    s32  phase;

    if (--g_Task->unk_09 == 0) {
        g_Task->facing      = g_BattleEffectBattler->facing;
        g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed;
        g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed;
        g_Task->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed;
        Battle_ProjectRange();
        angle_cell  = &D_1F800004;
        phase       = (g_Task->param.unk_0B & 7) << 8;
        *angle_cell = phase;
        phase += ANGLE_90;
        *angle_cell = phase + D_801EFC50[g_Task->facing];
        g_Task->unk_2E.half += (rsin(*angle_cell) * 72) >> 0xC;
        g_Task->unk_30.half += (rcos(*angle_cell) * 72) >> 0xC;
        g_Task->unk_14 = D_801EFC50[g_Task->facing];
        if (LOHU(g_Battle.action_id) == ABILITY_TEMPEST) {
            g_Task->param.unk_0B = 0;
        } else {
            g_Task->param.unk_0B = 0x10;
        }
        g_Task->unk_09 = 0;
        g_Task->timer  = 0;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF628(void) {
    s32 offset;
    u8  timer;

    g_Task->unk_2E.half += (rsin(g_Task->unk_14) * 8) >> 0xC;
    offset = (rcos(g_Task->unk_14) * 8) >> 0xC;
    g_Task->unk_30.half += offset;
    g_Task->unk_09 += 1;
    timer         = g_Task->timer + 4;
    g_Task->timer = timer;
    if ((timer & BYTE_MASK) == 16) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF6E0(void) {
    s32 cosine;

    g_Task->unk_2E.half += (rsin(g_Task->unk_14) * 0x18) >> 0xC;
    cosine = rcos(g_Task->unk_14);
    g_Task->unk_30.half += (cosine * 0x18) >> 0xC;
    g_Task->unk_09 += 1;
    if (g_Task->unk_09 == 0x14) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        Actor_Clear();
    }
}

INCLUDE_ASM(func_801EF7A8);

/* func_801EFB78 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801EFBDC */
#include "overlays/bmagic/Actor_Clear.h"

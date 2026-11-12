#include "magic074_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC28(void) {
    PartyMember* saved;
    u8           i;

    BMagic_DispatchTaskPair(func_801EED18, Effect_StartOnZeroTick);

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        if (BMAGIC_EFFECT_SLOTS[i].header.flags & BMAGIC_EFFECT_IN_USE) {
            saved                 = g_BattleEffectBattler;
            D_801F20DC            = &BMAGIC_EFFECT_SLOTS[i];
            g_BattleEffectBattler = BMAGIC_EFFECT_SLOTS[i].battler;
            func_801EF710();
            g_BattleEffectBattler = saved;
        }
    }
}

INCLUDE_ASM(func_801EED18);

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

/* func_801EEF9C */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEFE0(void) {
    BMagicEffectFuncs handlers;

    BMAGIC_DISPATCH_STEP_HANDLERS(D_801EEC04, header.step);
}

INCLUDE_ASM(func_801EF058);

#include "overlays/bmagic/Effect_ReplaceSlotPaletteFade.h"

#include "overlays/bmagic/Effect_FadePaletteIn.h"

/* func_801EF4D0 */
#include "overlays/bmagic/Effect_NextStepUnderTickLimit.h"

MATCH void func_801EF518(void) {
    u8           unk04;
    PartyMember* battler;

    unk04 = g_Task->unk_04;
    if (unk04 < 3) {
        battler = &g_Game.members[unk04];
    } else {
        battler = (PartyMember*)((EnemyBattler*)g_BattleEnemies + unk04);
    }
    g_PaletteFades[g_Task->timer].offset.red--;
    g_PaletteFades[g_Task->timer].offset.green--;
    g_PaletteFades[g_Task->timer].offset.blue--;
    if (--g_Task->unk_09 == 0) {
        func_80196718(battler);
        func_800AF814(g_Task->unk_04);
        g_Task->header.step++;
    }
}

/* func_801EF6A4 */
#include "overlays/bmagic/Effect_FinishRecovery.h"

MATCH void func_801EF710(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 1), 1, D_801F20DC);
}

MATCH void func_801EF754(void) {
    Magic074Steps handlers;
    u8            radius;

    handlers = D_801EEC1C;
    handlers.steps[D_801F20DC->header.step]();
    if ((D_801F20DC->header.flags & BMAGIC_EFFECT_IN_USE) && D_801F20DC->header.step != 0) {
        func_801F00B0();
        if (D_801F20DC->phase_0C & 0x3) {
            Effect_DrawSparkleRays(g_FrameCount >> 1, D_801F20DC->unk_06);
            radius = D_801F20DC->unk_06;
            func_801EFE18((g_FrameCount >> 1) + 4, radius + (radius >> 1));
        }
    }
}

#include "overlays/bmagic/Effect_LaunchSparkle.h"

MATCH void func_801EFA50(void) {
    s32 wave;
    u16 phase;
    u8  tick;

    BMAGIC_SWAY_ADVANCE_WORK(D_801F20DC)
}

MATCH void func_801EFB00(void) {
    u16 phase;
    u8  timer;

    BMAGIC_SWAY_EFFECT_WORK(D_801F20DC, func_801F0440)
}

#include "overlays/bmagic/Effect_DrawSparkleRays.h"

INCLUDE_ASM(func_801EFE18);

INCLUDE_ASM(func_801F00B0);

/* func_801F03D4 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

MATCH void func_801F0440(void) {
    D_801F20DC->header.flags = 0;
    D_801F20DC->header.mode  = 0;
    D_801F20DC->header.step  = 0;
    D_801F20DC->unk_03       = 0;
    D_801F20DC->unk_04       = 0;
}

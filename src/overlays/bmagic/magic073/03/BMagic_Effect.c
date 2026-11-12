#include "magic073_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC28(void) {
    PartyMember* saved;
    u8           i;

    BMagic_DispatchTaskPair(func_801EED18, func_801EEF50);

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        if (BMAGIC_EFFECT_SLOTS[i].header.flags & BMAGIC_EFFECT_IN_USE) {
            saved                 = g_BattleEffectBattler;
            D_801F21F0            = &BMAGIC_EFFECT_SLOTS[i];
            g_BattleEffectBattler = BMAGIC_EFFECT_SLOTS[i].battler;
            func_801EF724();
            g_BattleEffectBattler = saved;
        }
    }
}

INCLUDE_ASM(func_801EED18);

MATCH void func_801EEF50(void) {
    u16* flags;

    if (g_Task->param.unk_0B == 0 && func_801F04A4() == 0) {
        BATTLE_RAISE_STATE(BATTLE_STATE_EFFECT_PLAYING);
        func_801E5988();
    }
}

/* func_801EEFB0 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEFF4(void) {
    BMagicEffectFuncs handlers;

    BMAGIC_DISPATCH_STEP_HANDLERS(D_801EEC04, header.step);
}

INCLUDE_ASM(func_801EF06C);

#include "overlays/bmagic/Effect_ReplaceSlotPaletteFade.h"

#include "overlays/bmagic/Effect_FadePaletteIn.h"

/* func_801EF4E4 */
#include "overlays/bmagic/Effect_NextStepUnderTickLimit.h"

MATCH void func_801EF52C(void) {
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

/* func_801EF6B8 */
#include "overlays/bmagic/Effect_FinishRecovery.h"

MATCH void func_801EF724(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 1), 1, D_801F21F0);
}

MATCH void func_801EF768(void) {
    Magic073Steps handlers;
    u8            radius;

    handlers = D_801EEC1C;
    handlers.steps[D_801F21F0->header.step]();
    if ((D_801F21F0->header.flags & BMAGIC_EFFECT_IN_USE) && D_801F21F0->header.step != 0) {
        func_801F00C4();
        if (D_801F21F0->phase_0C & 0x3) {
            Effect_DrawSparkleRays(g_FrameCount >> 1, D_801F21F0->unk_06);
            radius = D_801F21F0->unk_06;
            func_801EFE2C((g_FrameCount >> 1) + 4, radius + (radius >> 1));
        }
    }
}

#include "overlays/bmagic/Effect_LaunchSparkle.h"

MATCH void func_801EFA64(void) {
    s32 wave;
    u16 phase;
    u8  tick;

    BMAGIC_SWAY_ADVANCE_WORK(D_801F21F0)
}

MATCH void func_801EFB14(void) {
    u16 phase;
    u8  timer;

    BMAGIC_SWAY_EFFECT_WORK(D_801F21F0, func_801F0454)
}

#include "overlays/bmagic/Effect_DrawSparkleRays.h"

INCLUDE_ASM(func_801EFE2C);

INCLUDE_ASM(func_801F00C4);

/* func_801F03E8 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

MATCH void func_801F0454(void) {
    D_801F21F0->header.flags = 0;
    D_801F21F0->header.mode  = 0;
    D_801F21F0->header.step  = 0;
    D_801F21F0->unk_03       = 0;
    D_801F21F0->unk_04       = 0;
}

MATCH u8 func_801F04A4(void) {
    s32 i;
    s32 count;

    count = 0;
    i     = 0;
    do {
        if (!(func_801DB524((i + 3) & BYTE_MASK) & BYTE_MASK) && g_BattleEnemyBattlers[(i & BYTE_MASK) + 3].header.mode == 6) {
            count++;
        }
        i++;
    } while ((u32)(i & BYTE_MASK) < 8);
    i = 0;
    do {
        if (!(func_801DB524(i & BYTE_MASK) & BYTE_MASK) && g_Game.members[i & BYTE_MASK].header.mode == 6) {
            count++;
        }
        i++;
    } while ((u32)(i & BYTE_MASK) < 3);
    return count;
}

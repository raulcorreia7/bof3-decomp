#include "magic073_03.h"

#include "overlays/bmagic/shared/Effect_LaunchSparkleBurst.h"
#include "overlays/bmagic/shared/Effect_SpawnTargetFades.h"

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

MATCH void func_801EED18(void) {
    u32 slot;
    u8  i;
    u8  battler;
    u8  count;

    EFFECT_SPAWN_TARGET_FADES(0x26, 0);
}

MATCH void func_801EEF50(void) {
    u16* flags;

    if (TASK(PartyMember)->param.unk_0B == 0 && func_801F04A4() == 0) {
        BATTLE_RAISE_STATE(BATTLE_STATE_EFFECT_PLAYING);
        Effect_Reset();
    }
}

/* func_801EEFB0 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EEFF4(void) {
    BMagicEffectSteps handlers;

    BMAGIC_DISPATCH_STEP_HANDLERS(D_801EEC04, header.step);
}

MATCH void func_801EF06C(void) {
    PartyMember* battler;
    u8           slot;
    u8           index;
    u8           count;
    u8           i;

    EFFECT_LAUNCH_SPARKLE_BURST();
}

#include "overlays/bmagic/shared/Effect_ReplaceSlotPaletteFade.h"

#include "overlays/bmagic/shared/Effect_FadePaletteIn.h"

/* func_801EF4E4 */
#include "overlays/bmagic/shared/Effect_NextStepUnderTickLimit.h"

/* func_801EF52C */
#include "overlays/bmagic/shared/Effect_FadePoisonedBattlerPalette.h"

/* func_801EF6B8 */
#include "overlays/bmagic/shared/Effect_EndRecovery.h"

MATCH void func_801EF724(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 1), 1, D_801F21F0);
}

MATCH void func_801EF768(void) {
    Magic073Steps handlers;
    u8            radius;

    handlers = D_801EEC1C;
    handlers.steps[D_801F21F0->header.step]();
    if ((D_801F21F0->header.flags & BMAGIC_EFFECT_IN_USE) && D_801F21F0->header.step != 0) {
        Effect_SparkleDrawDisc();
        if (D_801F21F0->phase_0C & 0x3) {
            Effect_SparkleDrawRays(g_FrameCount >> 1, D_801F21F0->unk_06);
            radius = D_801F21F0->unk_06;
            Effect_SparkleDrawWedges((g_FrameCount >> 1) + 4, radius + (radius >> 1));
        }
    }
}

#include "overlays/bmagic/shared/Effect_SparkleLaunch.h"

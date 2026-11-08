#include "magic076_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC28);

INCLUDE_ASM(func_801EED48);

/* func_801EEF5C */
#include "overlays/bmagic/Effect_PreparePalette.h"

#include "overlays/bmagic/Effect_BrightenPalette.h"

/* func_801EF11C */
MATCH void Effect_NextStep(void) {
    BMagic_AdvanceEffectStep(1);
}

INCLUDE_ASM(func_801EF160);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* Whether the queued action is an ability other than Raise Dead (the spell or the skill). */
MATCH u8 func_801EF2E8(void) {
    if (LOBU(g_BattleActionType) == BATTLE_ACTION_ABILITY) {
        switch (LOHU(g_BattleActionId)) {
            case ABILITY_RAISE_DEAD:
            case ABILITY_RAISE_DEAD_SKILL:
                return 0;
            default:
                return 1;
            case ABILITY_RESURRECT:
                return 1;
        }
    }
    return 0;
}

MATCH void func_801EF330(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectModes, g_Task->header.mode);
}

MATCH void func_801EF374(void) {
    SYS_DISPATCH_BYTE(D_801F048C, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_800AF764();
        func_801EF698();
    }
}

MATCH void func_801EF3F4(void) {
    PartyMember* work;
    u8           timer;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        g_Task->unk_04    = g_BattleEffectBattler->unk_04;
        work              = g_Task;
        work->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed;
        work->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed;
        work->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed + 0x00C00000;
        g_Task->unk_09    = 0;
        g_Task->timer     = 0x3C;
        g_Task->header.step++;
    }
}

INCLUDE_ASM(func_801EF4A8);

#include "overlays/bmagic/Effect_CountDownAndStep.h"

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

INCLUDE_ASM(func_801EF698);

MATCH void func_801EF8A8(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 6), 1, g_Task);
}

INCLUDE_ASM(func_801EF8EC);

INCLUDE_ASM(func_801EFA60);

INCLUDE_ASM(func_801EFC30);

INCLUDE_ASM(func_801EFD60);

INCLUDE_ASM(func_801EFEA8);

INCLUDE_ASM(func_801F00FC);

/* func_801F03D4 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801F0438 */
MATCH void Actor_Clear(void) {
    BMagic_ResetLocalWork();
}

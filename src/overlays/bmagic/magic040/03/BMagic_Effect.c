#include "magic040_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_DispatchMode.h"

INCLUDE_ASM(func_801EEC80);

INCLUDE_ASM(func_801EEDFC);

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

/* func_801EEF48 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEF8C(void) {
    Magic040Steps handlers = D_801EEC10;
    u8            next_09;

    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.step);
    if ((g_Task->header.flags & BMAGIC_EFFECT_IN_USE) != 0 && g_Task->header.step != 0) {
        func_801EF7FC();
        func_801EF600(g_Task->unk_09, g_Task->timer * 3);
        next_09 = g_Task->unk_09 + 4;
        func_801EF600(next_09, g_Task->timer * 2);
    }
}

MATCH void func_801EF074(void) {
    g_Task->facing      = BATTLE_ACTIVE_WORK->facing;
    g_Task->pos.x.fixed = BATTLE_ACTIVE_WORK->pos.x.fixed;
    g_Task->pos.y.fixed = BATTLE_ACTIVE_WORK->pos.y.fixed;
    g_Task->pos.z.fixed = BATTLE_ACTIVE_WORK->pos.z.fixed;
    func_801EF430(g_Task);
    g_Task->unk_09 = 0;
    g_Task->timer  = 0;
    g_Task->header.step += 1;
}

#include "overlays/bmagic/Effect_CountUpTimersAndStep.h"

#include "overlays/bmagic/Effect_CountUpAndStepAt32.h"

/* func_801EF1D0 */
MATCH void Effect_CountDownTimer(void) {
    BMagic_CountDownEffectTimer(1);
}

void func_801EF388(void);

MATCH void func_801EF248(void) {
    Callback handlers[2] = {func_801EF2D8, func_801EF388};

    handlers[g_Task->header.step]();
    if (g_Task->header.flags & 0x1) {
        if (g_Task->header.step != 0) {
            func_801EFA3C();
        }
    }
}

MATCH void func_801EF2D8(void) {
    g_Task->facing      = g_BattleEffectBattler->facing;
    g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed;
    g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed;
    g_Task->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed;
    func_801EF430(g_Task);
    g_Task->param.unk_0B = 0xB;
    g_Task->unk_09       = 0;
    g_Task->timer        = 128;
    g_Task->header.step += 1;
}

MATCH void func_801EF388(void) {
    g_Task->param.unk_0B -= 1;
    g_Task->unk_09 += g_Task->param.unk_0B;
    g_Task->timer -= 12;
    if (g_Task->param.unk_0B == 0) {
        BATTLE_ACTIVE_WORK->param.unk_0B -= 1;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF430);

INCLUDE_ASM(func_801EF600);

INCLUDE_ASM(func_801EF7FC);

INCLUDE_ASM(func_801EFA3C);

#include "magic123_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC04);

INCLUDE_ASM(func_801EEDAC);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EF0C4 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF108(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 2), 2, g_Task);
}

MATCH void func_801EF14C(void) {
    u8 timer;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        g_Task->unk_2E.half = g_BattleEffectBattler->unk_2E.half;
        g_Task->unk_30.half = g_BattleEffectBattler->unk_30.half;
        if RANDOM_MASK (1) {
            g_Task->unk_14 = g_BattleEffectBattler->unk_14 + RANDOM_MASK(BYTE_MASK);
        } else {
            g_Task->unk_14 = g_BattleEffectBattler->unk_14 - RANDOM_MASK(BYTE_MASK);
        }
        g_Task->unk_03       = RANDOM_MASK(7);
        g_Task->unk_0C       = RANDOM_MASK(7) + 8;
        g_Task->param.unk_0B = rand();
        g_Task->unk_09       = RANDOM_MASK(0xF) + 8;
        g_Task->timer        = 2;
        g_Task->header.step += 1;
    }
}

INCLUDE_ASM(func_801EF28C);

MATCH void func_801EF4AC(void) {
    u8 timer;

    g_Task->param.unk_0B += 1;
    g_Task->unk_09 += 1;
    timer         = g_Task->timer - 1;
    g_Task->timer = timer;
    if (!(timer & BYTE_MASK)) {
        BATTLE_ACTIVE_WORK->param.unk_0B -= 1;
        Actor_Clear();
        return;
    }
    func_801EF9E0();
}

/* func_801EF550 */
MATCH void Effect_ClearEffect(void) {
    BATTLE_ACTIVE_WORK->param.unk_0B--;
    Actor_Clear();
}

INCLUDE_ASM(func_801EF584);

INCLUDE_ASM(func_801EF750);

INCLUDE_ASM(func_801EF9E0);

/* func_801EFCA0 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801EFD04 */
MATCH void Actor_Clear(void) {
    BMagic_ResetLocalWork();
}

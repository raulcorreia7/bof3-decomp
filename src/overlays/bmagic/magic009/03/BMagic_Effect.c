#include "magic009_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC28.h"

INCLUDE_ASM(func_801EEC98);

INCLUDE_ASM(func_801EEF08);

#include "overlays/bmagic/Effect_CountDownTimerNextStep.h"

#include "overlays/bmagic/Effect_NextStepOnZeroTick.h"

MATCH void func_801EF09C(void) {
    u16* battle_flags;

    battle_flags = &g_BattleState;
    *battle_flags |= 0x2004;
    func_800A9820(*(battle_flags = &g_BattleTargetSelector));
    func_801E5988();
}

MATCH void func_801EF0DC(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectModes, g_Task->header.mode);
}

MATCH void func_801EF120(void) {
    SYS_DISPATCH_BYTE(D_801EF8A4, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_801EF3B8();
    }
}

INCLUDE_ASM(func_801EF198);

#include "overlays/bmagic/Effect_CountUpTimersByTwoNextStep.h"

/* func_801EF340 */
MATCH void Effect_CountDownTimer(void) {
    BMagic_CountDownEffectTimer(1);
}

INCLUDE_ASM(func_801EF3B8);

MATCH void func_801EF6B0(void) {
    Magic009Steps handlers;

    handlers = D_801EEC18;
    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        func_8014D290();
    }
}

#include "overlays/bmagic/Effect_SetDuration.h"

MATCH void func_801EF788(void) {
    u8 temp_a0;
    u8 temp_v0;

    temp_a0 = g_Task->unk_09;
    if ((temp_a0 & BYTE_MASK) != 0xFF) {
        temp_v0        = temp_a0 - 1;
        g_Task->unk_09 = temp_v0;
        if (!(temp_v0 & BYTE_MASK)) {
            func_800AFC98(2, 5);
        }
    }
    if (func_8014DAEC() & BYTE_MASK) {
        g_Task->unk_09 = 8;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF814(void) {
    u8 count;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF87C(void) {
    func_801E5988();
}

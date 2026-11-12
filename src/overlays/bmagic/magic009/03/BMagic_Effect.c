#include "magic009_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC28.h"

INCLUDE_ASM(func_801EEC98);

MATCH void func_801EEF08(void) {
    u32 slot;
    u32 i;

    if (g_Task->param.unk_0B == 0) {
        i = 0;
        do {
            slot                               = Battle_AllocEffect(1, 42) & BYTE_MASK;
            g_BattleEffects[slot].target.party = g_Task;
            g_BattleEffects[slot].header.mode  = 0;
            g_BattleEffects[slot].unk_0B       = i;
            g_BattleEffects[slot].arg.unk_09   = i * 4 + 1;
            g_Task->param.unk_0B += 1;
            i++;
        } while (i < 3);
        func_800AEF98(4, 0);
        BATTLE_ACTIVE_WORK->header.flags &= ~PARTY_MEMBER_FLAG_HANDLER_BUSY;
        SND_QueueSelectionFx(EMI_CUE_ID(SND_BANK_COMMON, 0));
        g_Task->unk_09 = 8;
        g_Task->header.mode += 1;
    }
}

#include "overlays/bmagic/Effect_CountDownTimerNextStep.h"

#include "overlays/bmagic/Effect_NextStepOnZeroTick.h"

MATCH void func_801EF09C(void) {
    u16* battle_flags;

    battle_flags = &g_BattleState;
    *battle_flags |= 0x2004;
    Battle_MarkDamaged(*(battle_flags = &g_Battle.target_selector));
    func_801E5988();
}

/* func_801EF0DC */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

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
    u8 timer;
    u8 next;

    timer = g_Task->unk_09;
    if ((timer & BYTE_MASK) != 0xFF) {
        next           = timer - 1;
        g_Task->unk_09 = next;
        if (!(next & BYTE_MASK)) {
            func_800AFC98(2, 5);
        }
    }
    if (Actor_StepAnimOnce() & BYTE_MASK) {
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

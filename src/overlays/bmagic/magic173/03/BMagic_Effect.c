#include "magic173_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    Callback handlers[2] = {func_801EEC5C, func_801EED90};

    SYS_DISPATCH_TASK(handlers, 1, g_Task);
}

MATCH void func_801EEC5C(void) {
    u32          i;
    u8           slot;
    PartyMember* task;
    PartyMember* work;
    u16*         src;
    u16*         dst;

    g_Task->facing = g_BattleEffectBattler->facing;
    task           = g_Task;
    WorldPos_Copy(&task->pos, &g_BattleEffectBattler->pos);
    task->param.unk_0B = 0;
    g_Task->header.mode += 1;
    for (i = 0; i < 2; i++) {
        slot                               = Battle_AllocEffect(1, 24);
        work                               = g_Task;
        g_BattleEffects[slot].header.mode  = 0;
        g_BattleEffects[slot].unk_04       = i;
        g_BattleEffects[slot].target.party = work;
        g_Task->param.unk_0B += 1;
    }
    i   = 0;
    dst = MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW);
    src = MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW);
    for (; i < 256; i++) {
        *dst++ = *src++;
    }
    g_GfxPalettePending = 1;
    SND_QueueSelectionFx(EMI_CUE_ID(SND_BANK_COMMON, 0x00));
}

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EEDF0 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEE34(void) {
    SYS_DISPATCH_BYTE(D_801F0990, g_Task->header.step);
    if (g_Task->unk_04 != 0) {
        if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
            func_801EF4EC();
        }
    } else {
        if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
            func_801EFA34();
        }
    }
}

INCLUDE_ASM(func_801EEEEC);

INCLUDE_ASM(func_801EF148);

MATCH void func_801EF3D8(void) {
    u8 timer;

    if (g_Task->timer < 8U) {
        g_Task->param.unk_0B += 1;
        g_Task->timer += 1;
        Battle_ProjectRange();
        Effect_RecordTrail();
    }
    timer = g_Task->timer;
    if ((timer & BYTE_MASK) == 8) {
        g_Task->unk_09 = timer;
        g_Task->header.step += 1;
    }
}

/* func_801EF484 */
#include "overlays/bmagic/Effect_FinishTrail.h"

INCLUDE_ASM(func_801EF4EC);

INCLUDE_ASM(func_801EFA34);

/* func_801F02B0 */
#include "overlays/bmagic/Effect_RecordTrail.h"

/* func_801F03A0 */
#include "overlays/bmagic/Effect_ClearTrail.h"

MATCH void func_801F0488(void) {
    g_ScriptTable = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(D_801F09A0, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        Battle_ProjectRange();
        func_801F075C();
        if (g_Task->header.step < 3) {
            func_8014D290();
        }
    }
    g_ScriptTable = AREA_SCRIPT_TABLE;
}

MATCH void func_801F0540(void) {
    g_Task->unk_25      = 0x1D;
    g_Task->unk_26      = 0;
    g_Task->unk_27      = 0xA0;
    g_Task->unk_28      = 0;
    g_Task->unk_24      = 4;
    g_Task->unk_5D      = 0;
    g_Task->unk_5E      = 0;
    g_Task->unk_5F      = 0;
    g_Task->unk_5C      = 0;
    g_Task->unk_2A      = 0;
    g_Task->unk_29      = 3;
    g_Task->unk_2C.half = 0;
    g_Task->unk_2B      = 1;
    Actor_SelectScript(0U);
    g_Task->unk_09 = 0;
    g_Task->header.step += 1;
}

MATCH void func_801F0648(void) {
    u8 timer;

    Actor_StepAnimOnce();
    timer          = g_Task->unk_09 + 4;
    g_Task->unk_09 = timer;
    if (timer == 16) {
        g_Task->header.step = g_Task->header.step + 1;
    }
}

MATCH void func_801F06B0(void) {
    Actor_StepAnimOnce();
    if (Actor_StepAnimOnce() != 0u) {
        g_Task->header.step = g_Task->header.step + 1;
    }
}

#include "overlays/bmagic/Effect_TickOnTimerZero.h"
INCLUDE_ASM(func_801F075C);

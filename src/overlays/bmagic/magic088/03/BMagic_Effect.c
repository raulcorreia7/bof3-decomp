#include "magic088_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC20.h"

INCLUDE_ASM(func_801EECA4);

MATCH void func_801EEEF4(void) {
    PartyMember* battler;
    u8           value;

    battler        = g_Battle.selected_actor;
    value          = g_Task->unk_09 - 1;
    g_Task->unk_09 = value;
    if (!(value & BYTE_MASK)) {
        battler->unk_5C = 1;
        GFX_FreePaletteFadeTarget(battler);
        g_Task->timer  = GFX_AllocPaletteFade(battler, 0, 0, 0, 1);
        g_Task->unk_09 = 8;
        g_Task->header.mode += 1;
    }
}

MATCH void func_801EEFA0(void) {
    /* FAKE: retail keeps an 8-byte frame that no statement explains. */
    FAKE_STACK_PADS(u8, 8);
    u8 timer;

    g_PaletteFades[g_Task->timer].offset.red -= 1;
    g_PaletteFades[g_Task->timer].offset.green -= 1;
    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        g_Task->header.mode = g_Task->header.mode + 1;
    }
}

#include "overlays/bmagic/Effect_Pause.h"

INCLUDE_ASM(func_801EF0A8);

MATCH void func_801EF1AC(void) {
    u32 slot;

    if (g_Task->param.unk_0B != 0) {
        return;
    }
    if (func_800AED5C(D_800B6BF0[g_Task->unk_04], g_Battle.target_selector) & BYTE_MASK) {
        slot                               = Battle_AllocEffect(1, 72) & BYTE_MASK;
        g_BattleEffects[slot].target.party = g_Task;
        g_BattleEffects[slot].unk_04       = g_Task->unk_04 + 4;
        g_BattleEffects[slot].arg.unk_09   = 1;
        g_BattleEffects[slot].unk_0A       = 0;
        g_Task->param.unk_0B++;
    } else {
        slot                               = Battle_AllocEffect(1, 72) & BYTE_MASK;
        g_BattleEffects[slot].target.party = g_Task;
        g_BattleEffects[slot].unk_04       = 8;
        g_BattleEffects[slot].arg.unk_09   = 1;
        g_BattleEffects[slot].unk_0A       = 0;
        g_Task->param.unk_0B++;
    }
    g_Task->header.mode++;
}

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

MATCH s32 func_801EF34C(void) {
    s32 result;

    if (LOBU(g_Battle.action_type) == BATTLE_ACTION_ABILITY) {
        switch (LOHU(g_Battle.action_id)) {
            case ABILITY_WEAKEN:
            case 0xC0:
                result = 0;
                break;
            case ABILITY_MOLASSES:
            case ABILITY_SLOW:
            case 0xBE:
                result = 1;
                break;
            case ABILITY_TARBABY:
            case ABILITY_BLUNT:
            case 0xBF:
                result = 2;
                break;
            default:
                result = 3;
                break;
        }
    } else if (LOHU(g_Battle.action_id) == 0x112) {
        g_Battle.action_id = ABILITY_WEAKEN;
        result             = 0;
    } else {
        result = 3;
    }
    return result;
}

#include "overlays/bmagic/Effect_SetActorMatrix.h"

/* func_801EF4E0 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF524(void) {
    SYS_DISPATCH_BYTE(D_801F0030, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        Effect_SetActorMatrix();
        func_801EF68C();
        PopMatrix();
    }
}

#include "overlays/bmagic/Effect_CountUpAndStep.h"

#include "overlays/bmagic/Effect_StepWhileTickUnderTwo.h"

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

INCLUDE_ASM(func_801EF68C);

MATCH void func_801EF900(void) {
    SYS_DISPATCH_BYTE(D_801F005C, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        func_801EFAE8();
        func_801EFB34();
        PopMatrix();
    }
}

#include "overlays/bmagic/Effect_CountDownTimerStep.h"

#include "overlays/bmagic/Effect_CountUpAndStepAt32.h"

MATCH void func_801EFA2C(void) {
    u8 timer_next;

    timer_next    = g_Task->timer - 1;
    g_Task->timer = timer_next;
    if (!(timer_next & BYTE_MASK)) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EFA94(void) {
    PartyMember* work;

    work         = g_Task;
    work->unk_09 = work->unk_09 - 2;
    if (g_Task->unk_09 == 0) {
        func_801E5988();
    }
}

MATCH void func_801EFAE8(void) {
    s32 i;

    for (i = 0; i < 6; i++) {
        if (i & 0x1) {
            D_801F003C[i] = D_801F003C[i] - 1;
        } else {
            D_801F003C[i] = D_801F003C[i] + 1;
        }
    }
}

INCLUDE_ASM(func_801EFB34);

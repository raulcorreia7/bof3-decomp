#include "magic088_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* blocker: frame 0x30 against retail 0x38; first diff: 0x801EEC28. */
INCLUDE_ASM(func_801EEC20);

INCLUDE_ASM(func_801EECA4);

MATCH void func_801EEEF4(void) {
    PartyMember* battler;
    u8           value;

    battler        = g_BattleSelectedActor;
    value          = g_Task->unk_09 - 1;
    g_Task->unk_09 = value;
    if (!(value & 0xFF)) {
        battler->unk_5C = 1;
        GFX_FreePaletteFadeTarget(battler);
        g_Task->timer  = GFX_AllocPaletteFade(battler, 0, 0, 0, 1);
        g_Task->unk_09 = 8;
        g_Task->header.mode += 1;
    }
}

MATCH void func_801EEFA0(void) {
    /* FAKE: retail keeps an 8-byte frame that no statement explains. */
    STACK_PADS(u8, 8);
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

/* hint: the two palette-offset adds, the zero test and the actor local leave the frame 8 bytes small (24 against 32); first differing instruction: addiu sp,sp,-24 at +0x8; the retail body also loads the selected actor into a0 before the first store. */
INCLUDE_ASM(func_801EF0A8);

INCLUDE_ASM(func_801EF1AC);

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

MATCH s32 func_801EF34C(void) {
    s32 result;

    if (LOBU(g_BattleActionType) == BATTLE_ACTION_ABILITY) {
        switch (LOHU(g_BattleActionId)) {
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
    } else if (LOHU(g_BattleActionId) == 0x112) {
        g_BattleActionId = ABILITY_WEAKEN;
        result           = 0;
    } else {
        result = 3;
    }
    return result;
}

#include "overlays/bmagic/Effect_SetActorMatrix.h"

MATCH void func_801EF4E0(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectModes, g_Task->header.mode);
}

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
        if (i & 1) {
            D_801F003C[i] = D_801F003C[i] - 1;
        } else {
            D_801F003C[i] = D_801F003C[i] + 1;
        }
    }
}

INCLUDE_ASM(func_801EFB34);

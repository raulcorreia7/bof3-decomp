#include "magic088_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC20);

INCLUDE_ASM(func_801EECA4);

MATCH void func_801EEEF4(void) {
    PartyBattler* battler;
    u8            value;

    battler            = g_BattleSelectedActor;
    value              = g_SpadWork->unk_09 - 1;
    g_SpadWork->unk_09 = value;
    if (!(value & 0xFF)) {
        battler->unk_5C = 1;
        func_80196718(battler);
        g_SpadWork->unk_0A = func_8019651C(battler, 0, 0, 0, 1);
        g_SpadWork->unk_09 = 8;
        g_SpadWork->step_01 += 1;
    }
}

MATCH void func_801EEFA0(void) {
    /* FAKE: retail keeps an 8-byte frame that no statement explains. */
    STACK_PADS(u8, 8);
    u8 timer;

    D_80145BD4[g_SpadWork->unk_0A].red_offset -= 1;
    D_80145BD4[g_SpadWork->unk_0A].green_offset -= 1;
    timer              = g_SpadWork->unk_09 - 1;
    g_SpadWork->unk_09 = timer;
    if (timer == 0) {
        g_SpadWork->step_01 = g_SpadWork->step_01 + 1;
    }
}

MATCH void func_801EF070(void) {
    PartyBattler* work;

    work = g_SpadWork;
    if (work->unk_0B < 2) {
        work->step_01++;
    }
}

INCLUDE_ASM(func_801EF0A8);

INCLUDE_ASM(func_801EF1AC);

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

MATCH s32 func_801EF34C(void) {
    s32 result;

    if (LOBU(g_BattleActionType) == 4) {
        switch (LOHU(g_BattleActionId)) {
            case 0x5A:
            case 0xC0:
                result = 0;
                break;
            case 0x1E:
            case 0x58:
            case 0xBE:
                result = 1;
                break;
            case 0x1F:
            case 0x59:
            case 0xBF:
                result = 2;
                break;
            default:
                result = 3;
                break;
        }
    } else if (LOHU(g_BattleActionId) == 0x112) {
        g_BattleActionId = 0x5A;
        result           = 0;
    } else {
        result = 3;
    }
    return result;
}

#include "overlays/bmagic/Effect_SetActorMatrix.h"

MATCH void func_801EF4E0(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

MATCH void func_801EF524(void) {
    SYS_DISPATCH_BYTE(D_801F0030, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0) {
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
    SYS_DISPATCH_BYTE(D_801F005C, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        Effect_SetActorMatrix();
        func_801EFAE8();
        func_801EFB34();
        PopMatrix();
    }
}

#include "overlays/bmagic/Effect_CountDownTimerStep.h"

MATCH void func_801EF9DC(void) {
    u8 timer;

    timer              = g_SpadWork->unk_09 + 1;
    g_SpadWork->unk_09 = timer;
    if (timer == 32) {
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 1;
    }
}

INCLUDE_ASM(func_801EFA2C);

MATCH void func_801EFA94(void) {
    PartyBattler* work;

    work         = g_SpadWork;
    work->unk_09 = work->unk_09 - 2;
    if (g_SpadWork->unk_09 == 0) {
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

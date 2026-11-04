#include "magic082_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC1C.h"

INCLUDE_ASM(func_801EEC94);

MATCH void func_801EEF0C(void) {
    PartyBattler* battler;
    u8            value;

    battler            = g_BattleSelectedActor;
    value              = g_SpadWork->unk_09 - 1;
    g_SpadWork->unk_09 = value;
    if (!(value & 0xFF)) {
        func_80196718(battler);
        g_SpadWork->unk_0A = func_8019651C(battler, 0, 0, 0, 1);
        g_SpadWork->unk_09 = 8;
        g_SpadWork->step_01 += 1;
    }
}

INCLUDE_ASM(func_801EEFB4);

#include "overlays/bmagic/Effect_NextStep.h"

INCLUDE_ASM(func_801EF10C);

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

INCLUDE_ASM(func_801EF3A0);

#include "overlays/bmagic/Effect_SetActorMatrix.h"

MATCH void func_801EF56C(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

MATCH void func_801EF5B0(void) {
    SYS_DISPATCH_BYTE(D_801F0D1C, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0) {
        Effect_SetActorMatrix();
        func_801EFA00();
        func_801EF720();
        PopMatrix();
    }
}

#include "overlays/bmagic/Effect_CountUpAndStep.h"

#include "overlays/bmagic/Effect_StepWhileTickUnderThree.h"

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

INCLUDE_ASM(func_801EF720);

INCLUDE_ASM(func_801EFA00);

MATCH void func_801EFD30(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectFuncs + 5), 2, g_SpadWork);
}

#include "overlays/bmagic/Effect_CountDownAndStep.h"

INCLUDE_ASM(func_801EFDC0);

INCLUDE_ASM(func_801EFEF4);

INCLUDE_ASM(func_801EFFE8);

MATCH void func_801F00DC(void) {
    s32 value;
    s32 value2;
    u8  value3;

    func_800AF764();
    if ((g_SpadWork->unk_0C == 4) && ((u8)g_SpadWork->unk_0A < 5U)) {
        value2 = (rand() & 3) | 0x40;
    } else {
        value2 = (rand() & 3) | 0x18;
    }
    func_801F0A84(value2);
    Effect_SetActorMatrix();
    func_801F03E0();
    PopMatrix();
    if (g_SpadWork->unk_0C < 4) {
        value              = g_SpadWork->unk_10 + 1;
        g_SpadWork->unk_10 = value;
        if (!(value & 7)) {
            g_SpadWork->unk_0C += 1;
        }
    }
    g_SpadWork->unk_09 += g_SpadWork->unk_0C;
    if (g_SpadWork->unk_0C == 4) {
        value3             = g_SpadWork->unk_0A - 1;
        g_SpadWork->unk_0A = value3;
        if (!(value3 & 0xFF)) {
            if (g_SpadWork->unk_0B == 0) {
                SND_QueueSelectionFx(0x101);
            }
            g_SpadWork->unk_10 = 8;
            g_SpadWork->unk_14 = 8;
            g_SpadWork->unk_20 = 8;
            g_SpadWork->unk_02 += 1;
        }
    }
}

INCLUDE_ASM(func_801F0260);

INCLUDE_ASM(func_801F03E0);

INCLUDE_ASM(func_801F0A84);

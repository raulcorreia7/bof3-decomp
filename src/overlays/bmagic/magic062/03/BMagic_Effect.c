#include "magic062_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC1C.h"

INCLUDE_ASM(func_801EEC94);

#include "overlays/bmagic/Effect_CountDownTimerLoadCounter.h"

INCLUDE_ASM(func_801EEF68);

#include "overlays/bmagic/Effect_NextStep.h"

INCLUDE_ASM(func_801EF0C0);

INCLUDE_ASM(func_801EF2A0);

INCLUDE_ASM(func_801EF2F0);

#include "overlays/bmagic/Effect_SetActorMatrix.h"

MATCH void func_801EF4C4(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

MATCH void func_801EF508(void) {
    SYS_DISPATCH_BYTE(D_801F0C18, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0) {
        Effect_SetActorMatrix();
        func_801EF678();
        func_801EF934();
        PopMatrix();
    }
}

#include "overlays/bmagic/Effect_CountUpAndStep.h"

#include "overlays/bmagic/Effect_StepWhileTickUnderThree.h"

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

INCLUDE_ASM(func_801EF678);

INCLUDE_ASM(func_801EF934);

MATCH void func_801EFBBC(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectFuncs + 5), 2, g_SpadWork);
}

#include "overlays/bmagic/Effect_CountDownAndStep.h"

INCLUDE_ASM(func_801EFC4C);

INCLUDE_ASM(func_801EFD80);

INCLUDE_ASM(func_801EFE74);

MATCH void func_801EFF68(void) {
    s32 value;
    s32 value2;
    u8  value3;

    func_800AF764();
    if ((g_SpadWork->unk_0C == 4) && ((u8)g_SpadWork->word_08.byte.timer_0A < 5U)) {
        value2 = (rand() & 3) | 0x40;
    } else {
        value2 = (rand() & 3) | 0x18;
    }
    func_801F0910(value2);
    Effect_SetActorMatrix();
    func_801F026C();
    PopMatrix();
    if (g_SpadWork->unk_0C < 4) {
        value              = g_SpadWork->unk_10 + 1;
        g_SpadWork->unk_10 = value;
        if (!(value & 7)) {
            g_SpadWork->unk_0C += 1;
        }
    }
    g_SpadWork->word_08.byte.unk_09 += g_SpadWork->unk_0C;
    if (g_SpadWork->unk_0C == 4) {
        value3                            = g_SpadWork->word_08.byte.timer_0A - 1;
        g_SpadWork->word_08.byte.timer_0A = value3;
        if (!(value3 & 0xFF)) {
            if (g_SpadWork->word_08.byte.unk_0B == 0) {
                SND_QueueSelectionFx(0x101);
            }
            g_SpadWork->unk_10 = 8;
            g_SpadWork->unk_14 = 8;
            g_SpadWork->unk_20 = 8;
            g_SpadWork->unk_02 += 1;
        }
    }
}

INCLUDE_ASM(func_801F00EC);

INCLUDE_ASM(func_801F026C);

INCLUDE_ASM(func_801F0910);

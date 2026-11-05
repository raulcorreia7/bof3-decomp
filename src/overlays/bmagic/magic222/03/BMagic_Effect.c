#include "magic222_03.h"
#include "sys/scene.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_RunStep.h"

INCLUDE_ASM(func_801EEC70);

#include "overlays/bmagic/Effect_CountDownTimerQueueFx.h"

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EEEE0(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

INCLUDE_ASM(func_801EEF24);

INCLUDE_ASM(func_801EEFC8);

INCLUDE_ASM(func_801EF148);

#define BMAGIC_CAMERA_SWING_TICKS 0x16
#include "overlays/bmagic/Effect_SwingCameraAngle.h"

INCLUDE_ASM(func_801EF324);

MATCH void func_801EF448(void) {
    u8 count;

    count                           = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = count;
    if (!(count & 0xFF)) {
        g_SpadWork->flags_00 |= 0x20;
        g_SpadWork->unk_5C = 1;
        g_SpadWork->unk_5D = 0;
        g_SpadWork->unk_5E = 0;
        g_SpadWork->unk_5F = 0;
        g_SpadWork->unk_02 += 1;
    }
}

MATCH void func_801EF4F0(void) {
    g_SpadWork->unk_5D -= 0x10;
    g_SpadWork->unk_5E -= 0x10;
    g_SpadWork->unk_5F -= 0x10;
    g_SpadWork->unk_40 += 0x1800;
    if ((s8)g_SpadWork->unk_5D == -0x80) {
        D_801EB4E0->word_08.byte.unk_0B -= 1;
        func_801E5988();
    }
}

MATCH void func_801EF5A4(void) {
    SYS_DISPATCH_BYTE(D_801F0D7C, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        Effect_SetActorMatrix();
        func_801EF87C();
        func_801EFACC();
        PopMatrix();
    }
}

MATCH void func_801EF634(void) {
    PartyBattler* src;
    PartyBattler* dst;

    if (--g_SpadWork->word_08.byte.unk_09 == 0) {
        src                               = D_801EB4E0;
        dst                               = g_SpadWork;
        dst->coord_x_34                   = src->coord_x_34;
        dst->coord_y_38                   = src->coord_y_38;
        dst->word_3C                      = src->word_3C;
        dst->unk_14                       = 0;
        dst->word_08.byte.unk_09          = 0;
        g_SpadWork->word_08.byte.timer_0A = 0x26;
        g_SpadWork->unk_02++;
    }
}

MATCH void func_801EF6C8(void) {
    g_SpadWork->word_08.byte.unk_09 += 1;
    g_SpadWork->unk_14 += 6;
    if (g_SpadWork->word_08.byte.unk_09 == 0x10) {
        g_SpadWork->unk_02 += 1;
    }
}

#include "overlays/bmagic/Effect_CountDownAndStep.h"

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801EF87C);

INCLUDE_ASM(func_801EFACC);

MATCH void func_801EFDEC(void) {
    SYS_DISPATCH_BYTE(D_801F0D8C, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        func_801F0168();
        func_801F0218();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EFE74);

INCLUDE_ASM(func_801EFF7C);

INCLUDE_ASM(func_801F0070);

MATCH void Effect_SetActorMatrix_801F0168(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    BMAGIC_SET_ACTOR_MATRIX();
}

INCLUDE_ASM(func_801F0218);

MATCH void func_801F0504(void) {
    SYS_DISPATCH_BYTE(D_801F0D98, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        func_801F07A8();
        func_801F07A8();
    }
}

INCLUDE_ASM(func_801F0584);

#include "overlays/bmagic/Effect_CountUpByTwoAndStep.h"

MATCH void func_801F066C(void) {
    u8 timer;

    timer                             = g_SpadWork->word_08.byte.timer_0A - 1;
    g_SpadWork->word_08.byte.timer_0A = timer;
    if (timer == 0) {
        g_SpadWork->word_08.byte.timer_0A = 0x10;
        g_SpadWork->unk_02                = g_SpadWork->unk_02 + 1;
    }
}

MATCH void func_801F06C8(void) {
    PartyBattler* work;

    work = g_SpadWork;
    work->word_08.byte.unk_0B += 4;
    work = g_SpadWork;
    work->word_08.byte.timer_0A--;
    if (work->word_08.byte.timer_0A == 0) {
        work = g_SpadWork;
        work->unk_02++;
    }
}

MATCH void func_801F0730(void) {
    PartyBattler* work;
    PartyBattler* active;
    u8            count;

    work = g_SpadWork;
    work->word_08.byte.unk_0B += 4;
    work                      = g_SpadWork;
    count                     = work->word_08.byte.unk_09 - 1;
    work->word_08.byte.unk_09 = count;
    if (count == 0) {
        active = BATTLE_ACTIVE_WORK;
        active->word_08.byte.unk_0B--;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801F07A8);

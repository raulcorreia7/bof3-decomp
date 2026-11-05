#include "magic059_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC04);

INCLUDE_ASM(func_801EED0C);

INCLUDE_ASM(func_801EF118);

MATCH void func_801EF1E0(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

INCLUDE_ASM(func_801EF224);

MATCH void func_801EF4C4(void) {
    u8* work;

    g_SpadWork->word_08.byte.unk_09 = 0;
    g_SpadWork->word_08.byte.timer_0A = 0;
    work                    = (u8*)g_SpadWork;
    work[2] += 1;
}

MATCH void func_801EF504(void) {
    PartyBattler* work;

    work = g_SpadWork;
    work->word_08.byte.unk_09++;
    work = g_SpadWork;
    work->word_08.byte.timer_0A += 2;
    if (work->word_08.byte.timer_0A == 32) {
        work = g_SpadWork;
        work->unk_02++;
    }
}

MATCH void func_801EF570(void) {
    u8 timer;

    timer                           = g_SpadWork->word_08.byte.unk_09 + 1;
    g_SpadWork->word_08.byte.unk_09 = timer;
    if (timer == 0xA0) {
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 1;
    }
}

#include "overlays/bmagic/Effect_CountDownTimer.h"

MATCH void func_801EF638(void) {
    PartyBattler* src;
    SVECTOR       pos;
    SVECTOR       rot;
    MATRIX        matrix;
    long          flags;

    PushMatrix();
    src                              = (PartyBattler*)D_801EB4E0;
    rot.vx                           = 0;
    rot.vy                           = 0;
    rot.vz                           = 0;
    g_SpadWork->coord_x_34           = src->coord_x_34;
    g_SpadWork->coord_y_38           = src->coord_y_38;
    g_SpadWork->word_3C.half.span_3E = src->word_3C.half.span_3E;
    pos.vx                           = (g_SpadWork->coord_x_34.raw >> 9) - 0x4000;
    pos.vy                           = (g_SpadWork->coord_y_38.raw >> 9) - 0x4000;
    pos.vz                           = -g_SpadWork->word_3C.half.span_3E / 2;
    RotTrans(&pos, &matrix.t, &flags);
    RotMatrix(&rot, &matrix);
    MulMatrix2((MATRIX*)g_CameraMatrix, &matrix);
    SetRotMatrix(&matrix);
    SetTransMatrix(&matrix);
}

INCLUDE_ASM(func_801EF70C);

MATCH void func_801EFE48(void) {
    SYS_DISPATCH_TASK(g_BMagicEffectFuncs + 5, 1, g_SpadWork);
}

INCLUDE_ASM(func_801EFE8C);

INCLUDE_ASM(func_801F0018);

MATCH void func_801F0070(void) {
    PartyBattler* work;

    work = g_SpadWork;
    work->word_08.byte.unk_09++;
    work = g_SpadWork;
    work->word_08.byte.timer_0A++;
    if (work->word_08.byte.timer_0A == 32) {
        work = g_SpadWork;
        work->unk_02++;
    }
}

MATCH void func_801F00DC(void) {
    u8 timer;

    timer                           = g_SpadWork->word_08.byte.unk_09 + 1;
    g_SpadWork->word_08.byte.unk_09 = timer;
    if (timer == 160) {
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 1;
    }
}

MATCH void func_801F012C(void) {
    PartyBattler* work;
    u8            count;

    work = g_SpadWork;
    work->word_08.byte.unk_09++;
    work                        = g_SpadWork;
    count                       = work->word_08.byte.timer_0A - 1;
    work->word_08.byte.timer_0A = count;
    if (count == 0) {
        BATTLE_ACTIVE_WORK->word_08.byte.unk_0B--;
        Actor_Clear();
    }
}

INCLUDE_ASM(func_801F01A4);

/* func_801F0490 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801F04F4 */
MATCH void Actor_Clear(void) {
    Bmagic_ResetLocalWork();
}

INCLUDE_ASM(func_801F0544);

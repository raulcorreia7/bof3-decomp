#include "magic066_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_RunStep.h"

INCLUDE_ASM(func_801EEC70);

MATCH void func_801EEDB8(void) {
    u8            timer;
    u32           slot;
    PartyBattler* work;

    timer                           = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = timer;
    if (timer == 0) {
        slot                               = Battle_AllocEffect(1, 0x11) & BYTE_MASK;
        work                               = g_SpadWork;
        g_BattleEffects[slot].unk_01       = 1;
        g_BattleEffects[slot].target.party = work;
        /* FAKE: keeps the target selector read after the slot stores, as retail orders it. */
        MATCH_FAKE_BARRIER();
        func_800A9610(g_BattleTargetSelector, 0x20);
        g_SpadWork->step_01 = g_SpadWork->step_01 + 1;
    }
}

#include "overlays/bmagic/Effect_PlayOnIdleTick.h"

MATCH void func_801EEEBC(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

MATCH void func_801EEF00(void) {
    SYS_DISPATCH_BYTE(D_801F006C, g_SpadWork->unk_02);
    if (BATTLE_ACTIVE_WORK->word_08.byte.unk_0B != 0xFF) {
        Effect_SetActorMatrix();
        func_801EF158();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EEF78);

INCLUDE_ASM(func_801EEFF8);

INCLUDE_ASM(func_801EF04C);

MATCH void func_801EF0A4(void) {
    g_SpadWork->word_08.byte.unk_0B = (g_SpadWork->word_08.byte.unk_0B - 1) & 0x1F;
    g_SpadWork->unk_14 -= 2;
    g_SpadWork->unk_10 -= 2;
    if (g_SpadWork->unk_10 == 0x20) {
        g_SpadWork->unk_02++;
    }
}

INCLUDE_ASM(func_801EF108);

INCLUDE_ASM(func_801EF158);

#include "overlays/bmagic/Effect_SetActorMatrix.h"

MATCH void func_801EF834(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectFuncs + 7), 2, g_SpadWork);
}

INCLUDE_ASM(func_801EF878);

MATCH void func_801EF8C8(void) {
    u8 timer;

    func_801EF984();
    timer                           = g_SpadWork->word_08.byte.unk_09 + 1;
    g_SpadWork->word_08.byte.unk_09 = timer;
    if (timer == 0x60) {
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 1;
    }
}

INCLUDE_ASM(func_801EF930);

INCLUDE_ASM(func_801EF984);

INCLUDE_ASM(func_801EFCC8);

MATCH void func_801EFFB0(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    rot.vx = 3072;
    rot.vy = 0;
    rot.vz = 0;
    pos.vx = (g_SpadWork->coord_x_34.raw >> 9) - 0x4000;
    pos.vy = (g_SpadWork->coord_y_38.raw >> 9) - 0x4000;
    pos.vz = -g_SpadWork->word_3C.half.span_3E / 2;
    RotTrans(&pos, &matrix.t, &flags);
    RotMatrix(&rot, &matrix);
    MulMatrix2((MATRIX*)g_CameraMatrix, &matrix);
    SetRotMatrix(&matrix);
    SetTransMatrix(&matrix);
}

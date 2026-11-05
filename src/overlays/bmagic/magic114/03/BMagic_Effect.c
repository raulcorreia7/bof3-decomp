#include "magic114_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC44);

INCLUDE_ASM(func_801EEDA0);

MATCH void func_801EEE84(void) {
    u8 temp_v0;

    temp_v0                           = g_SpadWork->word_08.byte.timer_0A + 1;
    g_SpadWork->word_08.byte.timer_0A = temp_v0;
    if ((u32)(temp_v0 & 0xFF) >= 0x21U) {
        g_SpadWork->step_01 += 1;
        g_SpadWork->word_08.byte.unk_09 = 0;
    }
}

MATCH void func_801EEEE4(void) {
    u8 temp_v0;

    temp_v0                         = g_SpadWork->word_08.byte.unk_09 + 1;
    g_SpadWork->word_08.byte.unk_09 = temp_v0;
    if ((u32)(temp_v0 & 0xFF) >= 0x21U) {
        g_SpadWork->step_01 += 1;
        g_SpadWork->word_08.byte.unk_09 = 0;
    }
}

INCLUDE_ASM(func_801EEF44);

MATCH void func_801EEFFC(void) {
    u8 temp_v0;

    temp_v0                         = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        g_SpadWork->step_01 += 1;
        return;
    }
    func_801F0FBC();
}

MATCH void func_801EF060(void) {
    u8 temp_v0;

    temp_v0                           = g_SpadWork->word_08.byte.timer_0A - 1;
    g_SpadWork->word_08.byte.timer_0A = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        g_SpadWork->step_01 += 1;
        g_SpadWork->word_08.byte.unk_09 = 0x40;
    }
}

#include "overlays/bmagic/Effect_CountDownAndPlay.h"

INCLUDE_ASM(func_801EF128);

INCLUDE_ASM(func_801EF280);

MATCH void func_801EF6A8(void) {
    PartyBattler* src;
    SVECTOR       pos;
    SVECTOR       rot;
    MATRIX        matrix;
    long          flags;

    PushMatrix();
    rot.vx = 0;
    rot.vy = 0;
    rot.vz = ((g_SpadWork->word_08.byte.timer_0A & 0x1F) - 2) << 7;
    src    = (PartyBattler*)D_801EB4E0;
    pos.vx = (src->coord_x_34.raw >> 9) - 0x4000;
    pos.vy = (src->coord_y_38.raw >> 9) - 0x4000;
    pos.vz = -(src->word_3C.half.span_3E + 0x200) / 2;
    RotTrans(&pos, &matrix.t, &flags);
    RotMatrix(&rot, &matrix);
    MulMatrix2((MATRIX*)g_CameraMatrix, &matrix);
    SetRotMatrix(&matrix);
    SetTransMatrix(&matrix);
}

MATCH void func_801EF774(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

MATCH void func_801EF7B8(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectFuncs + 3), 2, g_SpadWork);
}

INCLUDE_ASM(func_801EF7FC);

INCLUDE_ASM(func_801EF8C0);

INCLUDE_ASM(func_801EFA80);

MATCH void func_801EFDD8(void) {
    SYS_DISPATCH_BYTE(D_801F1230, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        func_801F093C();
        func_801F04D4(g_SpadWork->word_08.byte.unk_0B);
        func_801F0004();
    }
}

INCLUDE_ASM(func_801EFE70);

MATCH void func_801EFF1C(void) {
    s32 value;

    g_SpadWork->unk_20 -= 5;
    if (g_SpadWork->unk_14 == 0x30) {
        func_800A9610(g_BattleTargetSelector, 0x10U);
    }
    value              = g_SpadWork->unk_14 + 2;
    g_SpadWork->unk_14 = value;
    if (value == 0xC0) {
        g_SpadWork->word_08.byte.unk_0B = 1;
        g_SpadWork->unk_02 += 1;
    }
}

MATCH void func_801EFFB0(void) {
    PartyBattler* work        = g_SpadWork;
    u8            timer       = work->word_08.byte.unk_09 - 1;
    work->word_08.byte.unk_09 = timer;
    work->unk_20 -= 5;
    work->unk_14 += 2;
    if (timer == 0) {
        func_801E5988();
    }
}

INCLUDE_ASM(func_801F0004);

INCLUDE_ASM(func_801F04D4);

INCLUDE_ASM(func_801F093C);

INCLUDE_ASM(func_801F0D08);

INCLUDE_ASM(func_801F0D6C);

MATCH void func_801F0E4C(void) {
    if (func_8014DAEC() & BYTE_MASK) {
        func_801E5988();
        return;
    }
    func_8014D290();
}

INCLUDE_ASM(func_801F0E90);

INCLUDE_ASM(func_801F0FBC);

#include "magic087_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC04);

INCLUDE_ASM(func_801EED04);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EF0A8(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

MATCH void func_801EF0EC(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectFuncs + 1), 2, g_SpadWork);
}

INCLUDE_ASM(func_801EF130);

INCLUDE_ASM(func_801EF2C0);

INCLUDE_ASM(func_801EF324);

INCLUDE_ASM(func_801EF4A0);

MATCH void func_801EF530(void) {
    PartyBattler* work;

    if (g_SpadWork->word_08.byte.unk_0B == 0x80) {
        work                      = (PartyBattler*)D_801EB4E0;
        work->word_08.byte.unk_0B = work->word_08.byte.unk_0B - 1;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF580);

MATCH void func_801EF958(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectFuncs + 6), 1, g_SpadWork);
}

INCLUDE_ASM(func_801EF99C);

MATCH void func_801EFA2C(void) {
    u8 value;

    value                           = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = value;
    if (!(value & 0xFF)) {
        g_SpadWork->unk_0C = 0x100;
        g_SpadWork->unk_18 = 4;
        if (g_SpadWork->step_01 != 0) {
            g_SpadWork->word_08.byte.unk_0B = 0;
            g_SpadWork->word_08.byte.unk_09 = 0;
        } else {
            g_SpadWork->word_08.byte.unk_0B = 8;
            g_SpadWork->word_08.byte.unk_09 = 0x1F;
        }
        g_SpadWork->word_08.byte.timer_0A = 0;
        g_SpadWork->unk_02 += 1;
    }
}

INCLUDE_ASM(func_801EFAD4);

MATCH void func_801EFCA0(void) {
    PartyBattler* active;
    PartyBattler* work;

    active = BATTLE_ACTIVE_WORK;
    if (active->word_08.byte.unk_0B == 130) {
        work         = SP_REF(PartyBattler*, 0x44u);
        work->unk_02 = work->unk_02 + 1;
    }
}

INCLUDE_ASM(func_801EFCE0);

MATCH void func_801EFD7C(void) {
    SYS_DISPATCH_BYTE(D_801F0540, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        func_801EFF50();
        func_801F0014();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EFE04);

INCLUDE_ASM(func_801EFE90);

MATCH void func_801EFF50(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    ;
    PushMatrix();
    rot.vx = 0;
    rot.vy = 0;
    rot.vz = (g_SpadWork->word_08.byte.unk_0B & 0x3f) << 6;
    pos.vx = (g_SpadWork->coord_x_34.raw >> 9) - 0x4000;
    pos.vy = (g_SpadWork->coord_y_38.raw >> 9) - 0x4000;
    pos.vz = -(g_SpadWork->word_3C.half.span_3E + 0x200) / 2;
    RotTrans(&pos, &matrix.t, &flags);
    RotMatrix(&rot, &matrix);
    MulMatrix2((MATRIX*)g_CameraMatrix, &matrix);
    SetRotMatrix(&matrix);
    SetTransMatrix(&matrix);
}

INCLUDE_ASM(func_801F0014);

/* func_801F04A4 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

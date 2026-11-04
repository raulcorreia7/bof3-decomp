#include "magic043_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC18);

INCLUDE_ASM(func_801EED30);

MATCH void func_801EEEF0(void) {
    PartyBattler* temp_s0;
    u8            temp_v0;

    temp_s0            = g_BattleSelectedActor;
    temp_v0            = g_SpadWork->unk_09 - 1;
    g_SpadWork->unk_09 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        func_80196718(temp_s0);
        g_SpadWork->unk_0A = func_8019651C(temp_s0, 0, 0, 0, 1);
        g_SpadWork->unk_09 = 4;
        g_SpadWork->step_01 += 1;
    }
}

INCLUDE_ASM(func_801EEF98);

INCLUDE_ASM(func_801EF0B4);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EF360(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

MATCH void func_801EF3A4(void) {
    SYS_DISPATCH_BYTE(D_801EFC8C, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        func_801EF72C();
        func_801EF7F8();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EF42C);

INCLUDE_ASM(func_801EF55C);

INCLUDE_ASM(func_801EF5E0);

INCLUDE_ASM(func_801EF64C);

/* Follows BMAGIC_PROJECT_ACTOR_MATRIX (bmagic.h), but rot.vx starts at 0x400 and a halfword
 * table indexed by the work byte at +0x08 feeds the rotation. */
MATCH void func_801EF72C(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    rot.vx = 0x400;
    rot.vy = D_801EFC9C[g_SpadWork->unk_08];
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

INCLUDE_ASM(func_801EF7F8);

INCLUDE_ASM(func_801EFC24);

#include "magic098_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    Bmagic_DispatchTaskPair(func_801EEC5C, func_801EEF38);
}

INCLUDE_ASM(func_801EEC5C);

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

MATCH void func_801EEF84(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

INCLUDE_ASM(func_801EEFC8);

INCLUDE_ASM(func_801EF124);

INCLUDE_ASM(func_801EF1B4);

INCLUDE_ASM(func_801EF334);

MATCH void func_801EF498(void) {
    PartyBattler* active;

    g_SpadWork->word_08.byte.unk_0B = g_SpadWork->word_08.byte.unk_0B + 1;
    g_SpadWork->word_08.byte.unk_0A = g_SpadWork->word_08.byte.unk_0A - 2;
    if (g_SpadWork->word_08.byte.unk_0A == 0) {
        active                      = BATTLE_ACTIVE_WORK;
        active->word_08.byte.unk_0B = active->word_08.byte.unk_0B - 1;
        func_801E5988();
    }
}

MATCH void func_801EF520(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    rot.vx = 0;
    rot.vy = 0;
    rot.vz = 512;
    pos.vx = (g_SpadWork->coord_x_34.raw >> 9) - 0x4000;
    pos.vy = (g_SpadWork->coord_y_38.raw >> 9) - 0x4000;
    pos.vz = -g_SpadWork->word_3C.half.span_3E / 2;
    RotTrans(&pos, &matrix.t, &flags);
    RotMatrix(&rot, &matrix);
    MulMatrix2((MATRIX*)g_CameraMatrix, &matrix);
    SetRotMatrix(&matrix);
    SetTransMatrix(&matrix);
}

INCLUDE_ASM(func_801EF5D4);

INCLUDE_ASM(func_801EFE24);

INCLUDE_ASM(func_801F00C4);

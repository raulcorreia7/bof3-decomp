#include "magic143_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    Callback handlers[2] = {func_801EEC5C, func_801EED24};

    SYS_DISPATCH_TASK(handlers, 1, g_SpadWork);
}

INCLUDE_ASM(func_801EEC5C);

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

MATCH void func_801EED70(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

INCLUDE_ASM(func_801EEDB4);

INCLUDE_ASM(func_801EEF10);

INCLUDE_ASM(func_801EEF78);

INCLUDE_ASM(func_801EF054);

MATCH void func_801EF100(void) {
    PartyBattler* active;

    g_SpadWork->word_08.byte.unk_0B = g_SpadWork->word_08.byte.unk_0B + 1;
    g_SpadWork->word_08.byte.unk_0A = g_SpadWork->word_08.byte.unk_0A - 2;
    if (g_SpadWork->word_08.byte.unk_0A == 0) {
        active                      = BATTLE_ACTIVE_WORK;
        active->word_08.byte.unk_0B = active->word_08.byte.unk_0B - 1;
        func_801E5988();
    }
}

MATCH void func_801EF188(void) {
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

INCLUDE_ASM(func_801EF23C);

/* Follows sce10eff func_801D218C (160 instructions) but draws through Area_AddCellPrim(x, y, 2, 12) and starts with a
 * 128 base length where the template has 64 (first difference li v0,64 against li v0,128 at +0x18; the frame is also 64
 * bytes against 56). */
INCLUDE_ASM(func_801EF9A4);

INCLUDE_ASM(func_801EFC74);

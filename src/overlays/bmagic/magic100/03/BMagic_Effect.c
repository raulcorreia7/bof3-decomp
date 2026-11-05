#include "magic100_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_RunStep.h"

INCLUDE_ASM(func_801EEC70);

MATCH void func_801EED9C(void) {
    if (g_SpadWork->word_08.byte.unk_09 != 0) {
        func_800A9610(g_BattleTargetSelector, 0x10U);
        g_SpadWork->step_01 += 1;
    }
}

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EEE58(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_SpadWork->step_01);
}

MATCH void func_801EEE9C(void) {
    SYS_DISPATCH_BYTE(D_801EFDD0, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        func_801EF434();
        func_801EF4E8();
        PopMatrix();
        func_801EF8E8();
        func_801EF9D4();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EEF3C);

INCLUDE_ASM(func_801EF0D8);

INCLUDE_ASM(func_801EF1DC);

/* Spin step: moves coord_x_34/coord_y_38 by unk_0C/unk_10, raises span_3E by 0x40, turns unk_20 by +-0x200 (mod 0x1000, direction unk_0B & 1), counts unk_0A down. Tried the m2c if/else into a s32/u32/u8 local, a ternary and in-place
 * updates: first differing instruction addiu v0,v0,512 retail against addiu a0,v0,512 (retail keeps the angle in v0, the candidate allocates a0). */
INCLUDE_ASM(func_801EF358);

MATCH void func_801EF434(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    ;
    PushMatrix();
    rot.vx = 0;
    rot.vy = 0;
    rot.vz = 0;
    pos.vx = (g_SpadWork->coord_x_34.raw >> 9) - 0x4000;
    pos.vy = (g_SpadWork->coord_y_38.raw >> 9) - 0x4000;
    pos.vz = -(g_SpadWork->word_3C.half.span_3E + 0x100) / 2;
    RotTrans(&pos, &matrix.t, &flags);
    RotMatrix(&rot, &matrix);
    MulMatrix2((MATRIX*)g_CameraMatrix, &matrix);
    SetRotMatrix(&matrix);
    SetTransMatrix(&matrix);
}

INCLUDE_ASM(func_801EF4E8);

INCLUDE_ASM(func_801EF8E8);

INCLUDE_ASM(func_801EF9D4);

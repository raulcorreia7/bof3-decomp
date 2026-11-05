#include "magic106_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC04);

INCLUDE_ASM(func_801EECE4);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EEEE0(void) {
    u8* work;

    work = D_801F05F8;
    D_801EF9C0[work[1]]();
}

INCLUDE_ASM(func_801EEF24);

INCLUDE_ASM(func_801EEFAC);

INCLUDE_ASM(func_801EF16C);

INCLUDE_ASM(func_801EF29C);

INCLUDE_ASM(func_801EF418);

MATCH void func_801EF52C(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;
    s32     off;

    PushMatrix();
    rot.vx = 0;
    rot.vy = 0;
    off    = FIELD(u16, D_801F05F8, 0xE) + 0x800;
    rot.vz = ((D_801F05F8[3] << 7) - off) & 0xFFF;
    pos.vx = (FIELD(s32, D_801F05F8, 0x10) >> 9) - 0x4000;
    pos.vy = (FIELD(s32, D_801F05F8, 0x14) >> 9) - 0x4000;
    pos.vz = -FIELD(s16, D_801F05F8, 0x1A) / 2;
    RotTrans(&pos, &matrix.t, &flags);
    RotMatrix(&rot, &matrix);
    MulMatrix2((MATRIX*)g_CameraMatrix, &matrix);
    SetRotMatrix(&matrix);
    SetTransMatrix(&matrix);
}

INCLUDE_ASM(func_801EF5F4);

INCLUDE_ASM(func_801EF914);

MATCH void func_801EF970(void) {
    D_801F05F8[0] = 0;
    D_801F05F8[1] = 0;
    D_801F05F8[2] = 0;
    D_801F05F8[3] = 0;
    D_801F05F8[4] = 0;
}

#include "magic106_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    PartyBattler* saved;
    PartyBattler* swap;
    s32           count;

    Bmagic_DispatchTaskPair(func_801EECE4, Effect_PlayOnZeroTick);
    count = 0;
    do {
        if (D_801EF9F8[(u8)count << 5] & 1) {
            saved      = D_801EB4E0;
            swap       = FIELD(PartyBattler*, D_801EFA14, (u8)count << 5);
            D_801F05F8 = D_801EF9F8 + ((u8)count << 5);
            D_801EB4E0 = swap;
            func_801EEEE0();
            D_801EB4E0 = saved;
        }
        count += 1;
    } while ((u8)count < 0x60);
}

INCLUDE_ASM(func_801EECE4);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EEEE0(void) {
    u8* work;

    work = D_801F05F8;
    D_801EF9C0[work[1]]();
}

MATCH void func_801EEF24(void) {
    SYS_DISPATCH_BYTE(D_801EF9C4, D_801F05F8[2]);
    if (D_801F05F8[0] != 0 && D_801F05F8[2] != 0) {
        func_801EF52C();
        func_801EF5F4();
        PopMatrix();
    }
}

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

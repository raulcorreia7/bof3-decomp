#include "magic106_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    PartyBattler* saved;
    PartyBattler* swap;
    s32           count;

    BMagic_DispatchTaskPair(func_801EECE4, Effect_PlayOnZeroTick);
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

#ifdef NON_MATCHING
NON_MATCHING void func_801EF418(void) {
    u8  timer;
    u8  spin;
    u8  counter;
    s32 cosTerm;
    s32 angle;

    angle                        = (FIELD(u16, D_801F05F8, 0xE) + 0x40) & 0xFFF;
    FIELD(u16, D_801F05F8, 0xE)  = angle;
    FIELD(s32, D_801F05F8, 0x10) = D_801EB4E0->pos.x.raw + rsin(angle) * FIELD(s16, D_801F05F8, 0xC);
    cosTerm                      = rcos((s16)FIELD(u16, D_801F05F8, 0xE)) * FIELD(s16, D_801F05F8, 0xC);
    counter                      = FIELD(u8, D_801F05F8, 0xB) + 1;
    spin                         = FIELD(u8, D_801F05F8, 0xA);
    FIELD(u16, D_801F05F8, 0x1A) = (u16)(FIELD(u16, D_801F05F8, 0x1A) + spin);
    FIELD(u8, D_801F05F8, 0xB)   = counter;
    FIELD(s32, D_801F05F8, 0x14) = D_801EB4E0->pos.y.raw + cosTerm;
    if (g_FrameCount & 1) {
        timer                    = FIELD(u8, D_801F05F8, 9) - 1;
        FIELD(u8, D_801F05F8, 9) = timer;
        if (!(timer & 0xFF)) {
            D_801EB4E0->unk_0B -= 1;
            func_801EF970();
        }
    }
}
#else
INCLUDE_ASM(func_801EF418);
#endif

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
    MulMatrix2(&g_CameraMatrix, &matrix);
    SetRotMatrix(&matrix);
    SetTransMatrix(&matrix);
}

INCLUDE_ASM(func_801EF5F4);

MATCH u32 func_801EF914(void) {
    u8 index;

    for (index = 0u; index < 0x60; index++) {
        if ((D_801EF9F8[index << 5] & 1) == 0) {
            D_801EF9F8[index << 5] |= 1;
            return index;
        }
    }
    return 0xFFu;
}

MATCH void func_801EF970(void) {
    D_801F05F8[0] = 0;
    D_801F05F8[1] = 0;
    D_801F05F8[2] = 0;
    D_801F05F8[3] = 0;
    D_801F05F8[4] = 0;
}

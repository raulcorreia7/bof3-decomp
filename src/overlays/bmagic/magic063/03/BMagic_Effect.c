#include "magic063_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

extern u8 D_801F0470[];
void      func_801EF340(void);
void      func_801EECF8(void);
void      Effect_StartOnZeroTick(void);

MATCH void func_801EEC18(void) {
    PartyBattler* saved;
    PartyBattler* swap;
    s32           count;

    Bmagic_DispatchTaskPair(func_801EECF8, Effect_StartOnZeroTick);
    count = 0;
    do {
        if (D_801F0454[(u8)count << 5] & 1) {
            saved      = D_801EB4E0;
            swap       = FIELD(PartyBattler*, D_801F0470, (u8)count << 5);
            D_801F1054 = D_801F0454 + ((u8)count << 5);
            D_801EB4E0 = swap;
            func_801EF340();
            D_801EB4E0 = saved;
        }
        count += 1;
    } while ((u8)count < 0x60);
}

INCLUDE_ASM(func_801EECF8);

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

MATCH void func_801EEF30(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_Task->mode);
}

MATCH void func_801EEF74(void) {
    BattleHandlerTable5 handlers;

    handlers = D_801EEC04;
    SYS_DISPATCH_TASK(handlers.handlers, 2, g_Task);
}

INCLUDE_ASM(func_801EEFE4);

INCLUDE_ASM(func_801EF110);

MATCH void func_801EF190(void) {
    if (g_Task->unk_0B == 0) {
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF1C8);

#include "overlays/bmagic/Effect_FinishOnZeroTick.h"

MATCH void func_801EF340(void) {
    SYS_DISPATCH_TASK(g_BMagicEffectFuncs + 1, 1, D_801F1054);
}

MATCH void func_801EF384(void) {
    SYS_DISPATCH_BYTE(D_801F040C, D_801F1054->step);
    if (D_801F1054->flags != 0 && D_801F1054->step != 0) {
        func_801EF994();
        func_801EFA5C();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EF40C);

INCLUDE_ASM(func_801EF5CC);

INCLUDE_ASM(func_801EF704);

INCLUDE_ASM(func_801EF880);

MATCH void func_801EF994(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;
    s32     off;

    PushMatrix();
    rot.vx = 0;
    rot.vy = 0;
    off    = FIELD(u16, D_801F1054, 0xE) + 0x800;
    rot.vz = (((D_801F1054)->unk_03 << 7) - off) & 0xFFF;
    pos.vx = ((D_801F1054)->unk_10 >> 9) - 0x4000;
    pos.vy = ((D_801F1054)->unk_14 >> 9) - 0x4000;
    pos.vz = -FIELD(s16, D_801F1054, 0x1A) / 2;
    RotTrans(&pos, &matrix.t, &flags);
    RotMatrix(&rot, &matrix);
    MulMatrix2((MATRIX*)g_CameraMatrix, &matrix);
    SetRotMatrix(&matrix);
    SetTransMatrix(&matrix);
}

INCLUDE_ASM(func_801EFA5C);

MATCH void func_801EFD7C(void) {
    SYS_DISPATCH_BYTE(D_801F0440, D_801F1054->step);
    if (D_801F1054->flags != 0 && D_801F1054->step != 0) {
        func_801EF994();
        func_801EFA5C();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EFE04);

INCLUDE_ASM(func_801EFF18);

INCLUDE_ASM(func_801EFFE8);

INCLUDE_ASM(func_801F00F0);

INCLUDE_ASM(func_801F0220);

MATCH u32 func_801F0354(void) {
    u8 index;

    for (index = 0u; index < 0x60; index++) {
        if ((D_801F0454[index << 5] & 1) == 0) {
            D_801F0454[index << 5] |= 1;
            return index;
        }
    }
    return 0xFFu;
}

MATCH void func_801F03B0(void) {
    D_801F1054->flags  = 0;
    D_801F1054->mode   = 0;
    D_801F1054->step   = 0;
    D_801F1054->unk_03 = 0;
    D_801F1054->unk_04 = 0;
}

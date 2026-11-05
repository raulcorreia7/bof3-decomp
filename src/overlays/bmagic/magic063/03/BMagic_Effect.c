#include "magic063_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC18);

INCLUDE_ASM(func_801EECF8);

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

MATCH void func_801EEF30(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

MATCH void func_801EEF74(void) {
    BattleHandlerTable5 handlers;

    handlers = D_801EEC04;
    SYS_DISPATCH_TASK(handlers.handlers, 2, g_SpadWork);
}

INCLUDE_ASM(func_801EEFE4);

INCLUDE_ASM(func_801EF110);

MATCH void func_801EF190(void) {
    if (g_SpadWork->word_08.byte.unk_0B == 0) {
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF1C8);

MATCH void func_801EF2E4(void) {
    if (g_SpadWork->word_08.byte.unk_0B == 0) {
        func_800A9820(g_SpadWork->unk_04);
        D_801EB4E0->word_08.byte.unk_0B -= 1;
        func_801E5988();
    }
}

MATCH void func_801EF340(void) {
    SYS_DISPATCH_TASK(g_BMagicEffectFuncs + 1, 1, D_801F1054);
}

MATCH void func_801EF384(void) {
    SYS_DISPATCH_BYTE(D_801F040C, D_801F1054->unk_02);
    if (D_801F1054->flags_00 != 0 && D_801F1054->unk_02 != 0) {
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
    SYS_DISPATCH_BYTE(D_801F0440, D_801F1054->unk_02);
    if (D_801F1054->flags_00 != 0 && D_801F1054->unk_02 != 0) {
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

INCLUDE_ASM(func_801F0354);

MATCH void func_801F03B0(void) {
    D_801F1054->flags_00 = 0;
    D_801F1054->step_01  = 0;
    D_801F1054->unk_02   = 0;
    D_801F1054->unk_03   = 0;
    D_801F1054->unk_04   = 0;
}

#include "magic100_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_RunStep.h"

/* Structurally complete; the candidate keeps the loop counter in t-regs and CSEs the work
 * reload, retail keeps them in $s0/$s1 and reloads g_Task each iteration (75 vs 67
 * instructions). Permuter tried: best 2030, 23 errors (2400 iterations). */
#ifdef NON_MATCHING
NON_MATCHING void func_801EEC70(void) {
    PartyBattler* src;
    PartyBattler* work;
    u32           offset;
    u32           counter;
    u32           value;
    s32           span;

    src               = BATTLE_ACTIVE_WORK;
    g_Task->facing    = src->facing;
    g_Task->pos.x.raw = src->pos.x.raw;
    g_Task->pos.y.raw = src->pos.y.raw;
    span              = g_BattleSelectedActor->pos.z.raw;
    g_Task->unk_09    = 0;
    g_Task->pos.z.raw = span;
    g_Task->unk_0B    = 0;
    g_Task->mode += 1;
    offset  = (Battle_AllocEffect(1, 0xA) & BYTE_MASK) * BATTLE_EFFECT_STRIDE;
    counter = 0;
    value   = 1;
    do {
        FIELD(u8, D_801EC331, offset)            = 0;
        FIELD(u8, D_801EC33B, offset)            = (u8)counter;
        FIELD(u8, D_801EC339, offset)            = (u8)value;
        work                                     = g_Task;
        FIELD(PartyBattler*, D_801EC3A4, offset) = work;
        work->unk_0B += 1;
        counter += 1;
        value += 2;
    } while (counter < 8);
    SND_QueueSelectionFx(0x100);
}
#else
INCLUDE_ASM(func_801EEC70);
#endif

MATCH void func_801EED9C(void) {
    if (g_Task->unk_09 != 0) {
        func_800A9610(g_BattleTargetSelector, 0x10U);
        g_Task->mode += 1;
    }
}

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EEE58(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_Task->mode);
}

MATCH void func_801EEE9C(void) {
    SYS_DISPATCH_BYTE(D_801EFDD0, g_Task->step);
    if (g_Task->flags != 0 && g_Task->step != 0) {
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

/* Spin step: moves x/y by unk_0C/unk_10, raises span_3E by 0x40, turns unk_20 by +-0x200 (mod 0x1000, direction unk_0B & 1), counts unk_0A down. Tried the m2c if/else into a s32/u32/u8 local, a ternary and in-place
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
    pos.vx = (g_Task->pos.x.fixed >> 9) - 0x4000;
    pos.vy = (g_Task->pos.y.fixed >> 9) - 0x4000;
    pos.vz = -(g_Task->pos.z.part.integer + 0x100) / 2;
    RotTrans(&pos, &matrix.t, &flags);
    RotMatrix(&rot, &matrix);
    MulMatrix2((MATRIX*)g_CameraMatrix, &matrix);
    SetRotMatrix(&matrix);
    SetTransMatrix(&matrix);
}

INCLUDE_ASM(func_801EF4E8);

#ifdef NON_MATCHING
NON_MATCHING void func_801EF8E8(void) {
    SVECTOR       pos;
    SVECTOR       rot;
    MATRIX        matrix;
    long          flags;
    s32           height;
    PartyBattler* work;

    PushMatrix();
    work   = g_Task;
    rot.vx = 0;
    rot.vy = 0;
    rot.vz = 0;
    pos.vx = (work->pos.x.raw >> 9) - 0x4000;
    pos.vy = (work->pos.y.raw >> 9) - 0x4000;
    if (work->step < 3) {
        height = -work->pos.z.half.hi;
    } else {
        height = -(s16)Area_SampleHeight(work->pos.x.raw, work->pos.y.raw);
    }
    pos.vz = height / 2;
    RotTrans(&pos, &matrix.t, &flags);
    RotMatrix(&rot, &matrix);
    MulMatrix2((MATRIX*)g_CameraMatrix, &matrix);
    SetRotMatrix(&matrix);
    SetTransMatrix(&matrix);
}
#else
INCLUDE_ASM(func_801EF8E8);
#endif

INCLUDE_ASM(func_801EF9D4);

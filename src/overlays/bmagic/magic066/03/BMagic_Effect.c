#include "magic066_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_RunStep.h"

INCLUDE_ASM(func_801EEC70);

MATCH void func_801EEDB8(void) {
    u8            timer;
    u32           slot;
    PartyBattler* work;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        slot                               = Battle_AllocEffect(1, 0x11) & BYTE_MASK;
        work                               = g_Task;
        g_BattleEffects[slot].mode         = 1;
        g_BattleEffects[slot].target.party = work;
        /* FAKE: keeps the target selector read after the slot stores, as retail orders it. */
        MATCH_FAKE_BARRIER();
        func_800A9610(g_BattleTargetSelector, 0x20);
        g_Task->mode = g_Task->mode + 1;
    }
}

#include "overlays/bmagic/Effect_PlayOnIdleTick.h"

MATCH void func_801EEEBC(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_Task->mode);
}

MATCH void func_801EEF00(void) {
    SYS_DISPATCH_BYTE(D_801F006C, g_Task->step);
    if (BATTLE_ACTIVE_WORK->unk_0B != 0xFF) {
        Effect_SetActorMatrix();
        func_801EF158();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EEF78);

INCLUDE_ASM(func_801EEFF8);

MATCH void func_801EF04C(void) {
    s32 phase;

    g_Task->unk_0B = (g_Task->unk_0B - 1) & 0x1F;
    phase          = g_Task->unk_10 + 2;
    g_Task->unk_10 = phase;
    if (phase == 0x80) {
        g_Task->step += 1;
    }
}

MATCH void func_801EF0A4(void) {
    g_Task->unk_0B = (g_Task->unk_0B - 1) & 0x1F;
    g_Task->unk_14 -= 2;
    g_Task->unk_10 -= 2;
    if (g_Task->unk_10 == 0x20) {
        g_Task->step++;
    }
}

MATCH void func_801EF108(void) {
    s32 count;

    count = g_Task->unk_10 - 1;
    g_Task->unk_14 -= 2;
    g_Task->unk_10 = count;
    if (count == 0) {
        D_801EB4E0->unk_0B = 0xFF;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF158);

#include "overlays/bmagic/Effect_SetActorMatrix.h"

MATCH void func_801EF834(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectFuncs + 7), 2, g_Task);
}

MATCH void func_801EF878(void) {
    u32 i;

    for (i = 0; i < 4; i++) {
        D_801F00B0[i] = 0;
    }
    g_Task->unk_09 = 0;
    g_Task->step += 1;
}

MATCH void func_801EF8C8(void) {
    u8 timer;

    func_801EF984();
    timer          = g_Task->unk_09 + 1;
    g_Task->unk_09 = timer;
    if (timer == 0x60) {
        g_Task->step = g_Task->step + 1;
    }
}

MATCH void func_801EF930(void) {
    u8 temp_v1;

    func_801EF984();
    temp_v1        = g_Task->unk_09 + 1;
    g_Task->unk_09 = temp_v1;
    if ((temp_v1 & 0xFF) == 0x80) {
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF984);

INCLUDE_ASM(func_801EFCC8);

MATCH void func_801EFFB0(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    rot.vx = 3072;
    rot.vy = 0;
    rot.vz = 0;
    pos.vx = (g_Task->pos.x.fixed >> 9) - 0x4000;
    pos.vy = (g_Task->pos.y.fixed >> 9) - 0x4000;
    pos.vz = -COORD_INT(g_Task->pos.z) / 2;
    RotTrans(&pos, &matrix.t, &flags);
    RotMatrix(&rot, &matrix);
    MulMatrix2((MATRIX*)g_CameraMatrix, &matrix);
    SetRotMatrix(&matrix);
    SetTransMatrix(&matrix);
}

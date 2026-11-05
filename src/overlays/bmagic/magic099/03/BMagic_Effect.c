#include "magic099_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC18.h"

INCLUDE_ASM(func_801EEC88);

INCLUDE_ASM(func_801EEE70);

MATCH void func_801EEF98(void) {
    PartyBattler* work;

    work = g_SpadWork;
    if (work->word_08.byte.unk_0B != 0) {
        work->word_08.byte.unk_09 = 8;
        work                      = g_SpadWork;
        work->step_01             = work->step_01 + 1;
    }
}

INCLUDE_ASM(func_801EEFDC);

MATCH void func_801EF0EC(void) {
    if (g_SpadWork->word_08.byte.unk_0B == 9) {
        func_80196718(g_BattleSelectedActor);
        func_800AF814(g_BattleTargetSelector);
        func_800A9820(g_BattleTargetSelector);
        g_BattleState |= 4;
        func_801E5988();
    }
}

MATCH void func_801EF16C(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_SpadWork->step_01);
}

#include "overlays/bmagic/Effect_SetActorMatrixRolled.h"

MATCH void func_801EF264(void) {
    D_801F09A0[g_SpadWork->unk_02]();
    func_800AF764();
    if (g_SpadWork->unk_02 != 0) {
        Effect_SetActorMatrixRolled();
        func_801EF8F0(0x60, 0x20, 7);
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EF2EC);

MATCH void func_801EF374(void) {
    BattleEffectTimerStep();
}

#include "overlays/bmagic/Effect_CountDownTimerRaiseTicker.h"

MATCH void func_801EF44C(void) {
    PartyBattler* work;
    PartyBattler* active;
    u8            count;

    work = g_SpadWork;
    work->word_08.byte.unk_0B++;
    work                        = g_SpadWork;
    count                       = work->word_08.byte.timer_0A - 1;
    work->word_08.byte.timer_0A = count;
    if (count == 0) {
        active = BATTLE_ACTIVE_WORK;
        active->word_08.byte.unk_0B++;
        func_801E5988();
    }
}

MATCH void func_801EF4C4(void) {
    PartyBattler* work;

    work = g_SpadWork;
    D_801F09B0[work->unk_02]();
    func_800AF764();
    if (g_SpadWork->flags_00 != 0) {
        Effect_SetActorMatrixRolled();
        func_801EF8F0(0x20, 0x50, 0xF);
        func_801F070C();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EF554);

MATCH void func_801EF654(void) {
    BattleEffectTimerStep();
}

MATCH void func_801EF6C4(void) {
    MagicOrbitProjectionStep(0x28);
}

MATCH void func_801EF7D8(void) {
    PartyBattler* work;
    s32           counter;
    s32           angle;
    s32*          angle_cell;
    s32           velocity;

    g_SpadWork->word_08.byte.unk_0B++;

    work                   = g_SpadWork;
    counter                = work->unk_0C + 1;
    VOL(s32, work->unk_0C) = counter;
    angle                  = (counter & 0x7F) << 5;
    angle_cell             = &D_1F800004;
    *angle_cell            = angle;
    D_1F800000             = 0x28;

    velocity             = rcos(angle) * D_1F800000;
    work                 = g_SpadWork;
    work->coord_x_34.raw = BATTLE_ACTIVE_WORK->coord_x_34.raw + velocity;

    velocity                   = rsin(*angle_cell) * D_1F800000;
    g_SpadWork->coord_y_38.raw = BATTLE_ACTIVE_WORK->coord_y_38.raw + velocity;

    if (--g_SpadWork->word_08.byte.timer_0A == 0) {
        BATTLE_ACTIVE_WORK->word_08.byte.unk_0B++;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF8F0);

MATCH void func_801F0008(void) {
    D_801F09C0[g_SpadWork->unk_02]();
    func_800AF764();
    if (g_SpadWork->unk_02 != 0) {
        Effect_SetActorMatrixRolled();
        func_801F043C();
        func_801F070C();
        PopMatrix();
    }
}

MATCH void func_801F0090(void) {
    PartyBattler* work;
    s32           counter;
    s32           angle;
    s32*          angle_cell;
    s32           velocity;

    g_SpadWork->word_08.byte.unk_0B   = (u8)(RANDOM_MASK(0xF));
    g_SpadWork->word_08.byte.unk_09   = 0;
    g_SpadWork->word_08.byte.timer_0A = 0;

    work                   = g_SpadWork;
    counter                = (work->unk_03 << 5) + 0x10;
    angle                  = (counter & 0x7F) << 5;
    VOL(s32, work->unk_0C) = counter;
    angle_cell             = &D_1F800004;
    *angle_cell            = angle;
    D_1F800000             = 0x18;

    velocity                   = rcos(angle) * D_1F800000;
    g_SpadWork->coord_x_34.raw = BATTLE_ACTIVE_WORK->coord_x_34.raw + velocity;

    velocity                   = rsin(*angle_cell) * D_1F800000;
    g_SpadWork->coord_y_38.raw = BATTLE_ACTIVE_WORK->coord_y_38.raw + velocity;

    g_SpadWork->word_3C.half.span_3E = (u16)BATTLE_ACTIVE_WORK->word_3C.half.span_3E;
    g_SpadWork->unk_02++;
}

MATCH void func_801F01AC(void) {
    PartyBattler* work;

    work = g_SpadWork;
    if (work->word_08.byte.timer_0A < 16) {
        work->word_08.byte.timer_0A += 2;
    } else {
        work->word_08.byte.unk_09 = 60;
        work                      = g_SpadWork;
        work->unk_02++;
    }
}

MATCH void func_801F0200(void) {
    MagicOrbitProjectionStep(0x10);
}

MATCH void func_801F0314(void) {
    PartyBattler* work;
    PartyBattler* scratch;
    s32           counter;
    s32           angle;
    s32*          angle_cell;
    s32           velocity;

    g_SpadWork->word_08.byte.unk_0B++;

    work                   = g_SpadWork;
    counter                = work->unk_0C + 1;
    VOL(s32, work->unk_0C) = counter;
    angle                  = (counter & 0x7F) << 5;
    angle_cell             = &D_1F800004;
    *angle_cell            = angle;
    D_1F800000             = 0x18;

    velocity             = rcos(angle) * D_1F800000;
    work                 = g_SpadWork;
    work->coord_x_34.raw = BATTLE_ACTIVE_WORK->coord_x_34.raw + velocity;

    velocity                = rsin(*angle_cell) * D_1F800000;
    scratch                 = g_SpadWork;
    scratch->coord_y_38.raw = BATTLE_ACTIVE_WORK->coord_y_38.raw + velocity;
    scratch->word_08.byte.timer_0A -= 2;

    if (g_SpadWork->word_08.byte.timer_0A == 0) {
        BATTLE_ACTIVE_WORK->word_08.byte.unk_0B++;
        func_801E5988();
    }
}

/* Follows sce10eff func_801D218C (160 instructions) but draws through Area_AddCellPrim(x, y, 2, 12) with the vector
 * scaled by sra 3 into the call, so the frame is 64 bytes against 56 (first difference addiu sp at +0x0) */
INCLUDE_ASM(func_801F043C);

INCLUDE_ASM(func_801F070C);

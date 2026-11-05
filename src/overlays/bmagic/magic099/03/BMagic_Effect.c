#include "magic099_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC18.h"

INCLUDE_ASM(func_801EEC88);

INCLUDE_ASM(func_801EEE70);

MATCH void func_801EEF98(void) {
    PartyBattler* work;

    work = g_Task;
    if (work->unk_0B != 0) {
        work->unk_09 = 8;
        work         = g_Task;
        work->mode   = work->mode + 1;
    }
}

INCLUDE_ASM(func_801EEFDC);

MATCH void func_801EF0EC(void) {
    if (g_Task->unk_0B == 9) {
        func_80196718(g_BattleSelectedActor);
        func_800AF814(g_BattleTargetSelector);
        func_800A9820(g_BattleTargetSelector);
        g_BattleState |= 4;
        func_801E5988();
    }
}

MATCH void func_801EF16C(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_Task->mode);
}

#include "overlays/bmagic/Effect_SetActorMatrixRolled.h"

MATCH void func_801EF264(void) {
    D_801F09A0[g_Task->step]();
    func_800AF764();
    if (g_Task->step != 0) {
        Effect_SetActorMatrixRolled();
        func_801EF8F0(0x60, 0x20, 7);
        PopMatrix();
    }
}

MATCH void func_801EF2EC(void) {
    g_Task->unk_0B    = rand() & 0xF;
    g_Task->unk_09    = 0;
    g_Task->timer     = 0;
    g_Task->pos.x.raw = D_801EB4E0->pos.x.raw;
    g_Task->pos.y.raw = D_801EB4E0->pos.y.raw;
    g_Task->pos.z.raw = D_801EB4E0->pos.z.raw;
    g_Task->step += 1;
}

MATCH void func_801EF374(void) {
    BattleEffectTimerStep();
}

#include "overlays/bmagic/Effect_CountDownTimerRaiseTicker.h"

MATCH void func_801EF44C(void) {
    PartyBattler* work;
    PartyBattler* active;
    u8            count;

    work = g_Task;
    work->unk_0B++;
    work        = g_Task;
    count       = work->timer - 1;
    work->timer = count;
    if (count == 0) {
        active = BATTLE_ACTIVE_WORK;
        active->unk_0B++;
        func_801E5988();
    }
}

MATCH void func_801EF4C4(void) {
    PartyBattler* work;

    work = g_Task;
    D_801F09B0[work->step]();
    func_800AF764();
    if (g_Task->flags != 0) {
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

    g_Task->unk_0B++;

    work                   = g_Task;
    counter                = work->unk_0C + 1;
    VOL(s32, work->unk_0C) = counter;
    angle                  = (counter & 0x7F) << 5;
    angle_cell             = &D_1F800004;
    *angle_cell            = angle;
    D_1F800000             = 0x28;

    velocity        = rcos(angle) * D_1F800000;
    work            = g_Task;
    work->pos.x.raw = BATTLE_ACTIVE_WORK->pos.x.raw + velocity;

    velocity          = rsin(*angle_cell) * D_1F800000;
    g_Task->pos.y.raw = BATTLE_ACTIVE_WORK->pos.y.raw + velocity;

    if (--g_Task->timer == 0) {
        BATTLE_ACTIVE_WORK->unk_0B++;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF8F0);

MATCH void func_801F0008(void) {
    D_801F09C0[g_Task->step]();
    func_800AF764();
    if (g_Task->step != 0) {
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

    g_Task->unk_0B = (u8)(RANDOM_MASK(0xF));
    g_Task->unk_09 = 0;
    g_Task->timer  = 0;

    work                   = g_Task;
    counter                = (work->unk_03 << 5) + 0x10;
    angle                  = (counter & 0x7F) << 5;
    VOL(s32, work->unk_0C) = counter;
    angle_cell             = &D_1F800004;
    *angle_cell            = angle;
    D_1F800000             = 0x18;

    velocity          = rcos(angle) * D_1F800000;
    g_Task->pos.x.raw = BATTLE_ACTIVE_WORK->pos.x.raw + velocity;

    velocity          = rsin(*angle_cell) * D_1F800000;
    g_Task->pos.y.raw = BATTLE_ACTIVE_WORK->pos.y.raw + velocity;

    g_Task->pos.z.half.hi = (u16)BATTLE_ACTIVE_WORK->pos.z.half.hi;
    g_Task->step++;
}

MATCH void func_801F01AC(void) {
    PartyBattler* work;

    work = g_Task;
    if (work->timer < 16) {
        work->timer += 2;
    } else {
        work->unk_09 = 60;
        work         = g_Task;
        work->step++;
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

    g_Task->unk_0B++;

    work                   = g_Task;
    counter                = work->unk_0C + 1;
    VOL(s32, work->unk_0C) = counter;
    angle                  = (counter & 0x7F) << 5;
    angle_cell             = &D_1F800004;
    *angle_cell            = angle;
    D_1F800000             = 0x18;

    velocity        = rcos(angle) * D_1F800000;
    work            = g_Task;
    work->pos.x.raw = BATTLE_ACTIVE_WORK->pos.x.raw + velocity;

    velocity           = rsin(*angle_cell) * D_1F800000;
    scratch            = g_Task;
    scratch->pos.y.raw = BATTLE_ACTIVE_WORK->pos.y.raw + velocity;
    scratch->timer -= 2;

    if (g_Task->timer == 0) {
        BATTLE_ACTIVE_WORK->unk_0B++;
        func_801E5988();
    }
}

/* Follows sce10eff func_801D218C (160 instructions) but draws through Area_AddCellPrim(x, y, 2, 12) with the vector
 * scaled by sra 3 into the call, so the frame is 64 bytes against 56 (first difference addiu sp at +0x0) */
INCLUDE_ASM(func_801F043C);

INCLUDE_ASM(func_801F070C);

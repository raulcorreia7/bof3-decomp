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
    if (work->param.unk_0B != 0) {
        work->unk_09      = 8;
        work              = g_Task;
        work->header.mode = work->header.mode + 1;
    }
}

#include "overlays/bmagic/Effect_BrightenPalette.h"

MATCH void func_801EF0EC(void) {
    if (g_Task->param.unk_0B == 9) {
        GFX_FreePaletteFadeTarget(g_BattleSelectedActor);
        func_800AF814(g_BattleTargetSelector);
        func_800A9820(g_BattleTargetSelector);
        g_BattleState |= BATTLE_STATE_EFFECT_PLAYING;
        func_801E5988();
    }
}

MATCH void func_801EF16C(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_Task->header.mode);
}

#include "overlays/bmagic/Effect_SetActorMatrixRolled.h"

MATCH void func_801EF264(void) {
    D_801F09A0[g_Task->header.step]();
    func_800AF764();
    if (g_Task->header.step != 0) {
        Effect_SetActorMatrixRolled();
        func_801EF8F0(0x60, 0x20, 7);
        PopMatrix();
    }
}

MATCH void func_801EF2EC(void) {
    g_Task->param.unk_0B = RANDOM_MASK(0xF);
    g_Task->unk_09       = 0;
    g_Task->timer        = 0;
    g_Task->pos.x.fixed  = g_BattleEffectBattler->pos.x.fixed;
    g_Task->pos.y.fixed  = g_BattleEffectBattler->pos.y.fixed;
    g_Task->pos.z.fixed  = g_BattleEffectBattler->pos.z.fixed;
    g_Task->header.step += 1;
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
    work->param.unk_0B++;
    work        = g_Task;
    count       = work->timer - 1;
    work->timer = count;
    if (count == 0) {
        active = BATTLE_ACTIVE_WORK;
        active->param.unk_0B++;
        func_801E5988();
    }
}

MATCH void func_801EF4C4(void) {
    PartyBattler* work;

    work = g_Task;
    D_801F09B0[work->header.step]();
    func_800AF764();
    if (g_Task->header.flags != 0) {
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

    g_Task->param.unk_0B++;

    work                   = g_Task;
    counter                = work->unk_0C + 1;
    VOL(s32, work->unk_0C) = counter;
    angle                  = (counter & 0x7F) << 5;
    angle_cell             = &D_1F800004;
    *angle_cell            = angle;
    D_1F800000             = 0x28;

    velocity          = rcos(angle) * D_1F800000;
    work              = g_Task;
    work->pos.x.fixed = BATTLE_ACTIVE_WORK->pos.x.fixed + velocity;

    velocity            = rsin(*angle_cell) * D_1F800000;
    g_Task->pos.y.fixed = BATTLE_ACTIVE_WORK->pos.y.fixed + velocity;

    if (--g_Task->timer == 0) {
        BATTLE_ACTIVE_WORK->param.unk_0B++;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF8F0);

MATCH void func_801F0008(void) {
    D_801F09C0[g_Task->header.step]();
    func_800AF764();
    if (g_Task->header.step != 0) {
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

    g_Task->param.unk_0B = RANDOM_MASK(0xF);
    g_Task->unk_09       = 0;
    g_Task->timer        = 0;

    work                   = g_Task;
    counter                = (work->unk_03 << 5) + 0x10;
    angle                  = (counter & 0x7F) << 5;
    VOL(s32, work->unk_0C) = counter;
    angle_cell             = &D_1F800004;
    *angle_cell            = angle;
    D_1F800000             = 0x18;

    velocity            = rcos(angle) * D_1F800000;
    g_Task->pos.x.fixed = BATTLE_ACTIVE_WORK->pos.x.fixed + velocity;

    velocity            = rsin(*angle_cell) * D_1F800000;
    g_Task->pos.y.fixed = BATTLE_ACTIVE_WORK->pos.y.fixed + velocity;

    COORD_INT(g_Task->pos.z) = COORD_INT(BATTLE_ACTIVE_WORK->pos.z);
    g_Task->header.step++;
}

MATCH void func_801F01AC(void) {
    PartyBattler* work;

    work = g_Task;
    if (work->timer < 16) {
        work->timer += 2;
    } else {
        work->unk_09 = 60;
        work         = g_Task;
        work->header.step++;
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

    g_Task->param.unk_0B++;

    work                   = g_Task;
    counter                = work->unk_0C + 1;
    VOL(s32, work->unk_0C) = counter;
    angle                  = (counter & 0x7F) << 5;
    angle_cell             = &D_1F800004;
    *angle_cell            = angle;
    D_1F800000             = 0x18;

    velocity          = rcos(angle) * D_1F800000;
    work              = g_Task;
    work->pos.x.fixed = BATTLE_ACTIVE_WORK->pos.x.fixed + velocity;

    velocity             = rsin(*angle_cell) * D_1F800000;
    scratch              = g_Task;
    scratch->pos.y.fixed = BATTLE_ACTIVE_WORK->pos.y.fixed + velocity;
    scratch->timer -= 2;

    if (g_Task->timer == 0) {
        BATTLE_ACTIVE_WORK->param.unk_0B++;
        func_801E5988();
    }
}

/* blocker: frame 64 bytes against 56; first diff: addiu sp at +0x0. */
INCLUDE_ASM(func_801F043C);

INCLUDE_ASM(func_801F070C);

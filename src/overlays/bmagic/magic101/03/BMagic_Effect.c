#include "magic101_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC18(void) {
    BattleHandlerTable5 handlers;

    handlers = D_801EEC04;
    SYS_DISPATCH_BYTE(handlers.handlers, g_Task->header.mode);
    if (g_Task->timer != 0 && g_Task->header.flags != 0) {
        Effect_SetActorMatrix();
        func_801EF07C();
        PopMatrix();
    }
}

/* Three shapes tried (if/else per branch, read-then-condition-xor, shared-goto): gcc's
 * cross-jump merges the g_BattleActiveBattler tests or the facing reads (0x180 vs 0x19C);
 * retail keeps three separate D_8014637C loads and a shared xor block at 0x801EED50. First
 * diff 0x801EECE0, the side-mask test's target. Layout problem, not scheduling. */
#ifdef NON_MATCHING
NON_MATCHING void func_801EECCC(void) {
    u32 offset;
    u32 counter;
    u32 wave;
    u8  facing;

    if (g_BattleTargetSelector & BATTLE_TARGET_ENEMY_SIDE) {
        if (g_BattleActiveBattler >= BATTLE_PARTY_SLOT_COUNT) {
            facing = ((PartyBattler*)D_8014637C)->facing;
            goto have_facing;
        }
    } else if (g_BattleActiveBattler < BATTLE_PARTY_SLOT_COUNT) {
        facing = ((PartyBattler*)D_8014637C)->facing;
        goto have_facing;
    }
    facing = ((PartyBattler*)D_8014637C)->facing ^ 0x2;
have_facing:
    g_Task->facing = facing;
    func_800AFD9C();
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 0x30;
    g_Task->timer        = 0;
    g_Task->header.mode += 1;
    counter = 0;
    do {
        offset                                   = (Battle_AllocEffect(1, 0x1B) & BYTE_MASK) * BATTLE_EFFECT_STRIDE;
        wave                                     = (counter >> 2) * 3;
        wave                                     = (wave << 2) + 1;
        FIELD(u8, D_801EC331, offset)            = 0;
        FIELD(u8, D_801EC334, offset)            = (u8)counter;
        FIELD(u8, D_801EC339, offset)            = (u8)wave;
        FIELD(PartyBattler*, D_801EC3A4, offset) = g_Task;
        g_Task->param.unk_0B += 1;
        counter += 1;
    } while (counter < 0x10);
    SND_QueueSelectionFx(0x100);
}
#else
INCLUDE_ASM(func_801EECCC);
#endif

MATCH void func_801EEE68(void) {
    u8 timer;

    timer         = g_Task->timer + 1;
    g_Task->timer = timer;
    if (timer == 16) {
        func_800A9610(g_BattleTargetSelector, 0x10);
        g_Task->header.mode = g_Task->header.mode + 1;
    }
}

#include "overlays/bmagic/Effect_CountDownTimerNextStep.h"

MATCH void func_801EEF20(void) {
    u8 timer;

    timer         = g_Task->timer - 1;
    g_Task->timer = timer;
    if (timer == 0) {
        g_Task->header.mode = g_Task->header.mode + 1;
    }
}

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801EF07C);

MATCH void func_801EF310(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_Task->header.mode);
}

MATCH void func_801EF354(void) {
    SYS_DISPATCH_BYTE(D_801EFCE8, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_801EF78C();
        func_801EF88C();
        PopMatrix();
    }
}

#ifdef NON_MATCHING
NON_MATCHING void func_801EF3DC(void) {
    u8  counter;
    u8  angle;
    s32 value;

    counter        = g_Task->unk_09 - 1;
    g_Task->unk_09 = counter;
    if (!(counter & 0xFF)) {
        g_Task->facing       = D_801EB4E0->facing;
        g_Task->pos.x.raw    = D_801EB4E0->pos.x.raw;
        angle                = g_Task->unk_04;
        g_Task->pos.y.raw    = D_801EB4E0->pos.y.raw;
        g_Task->param.unk_0B = angle * 4 & 0x3F;
        g_Task->pos.z.raw    = D_801EB4E0->pos.z.raw + 0x01800000;
        value                = D_801EFCC0[g_Task->unk_04];
        g_Task->unk_10       = 0x60;
        angle                = g_Task->unk_04;
        g_Task->unk_14       = 0x20;
        g_Task->unk_09       = angle * 4 + 1;
        g_Task->unk_0C       = value << 8;
        g_Task->timer        = 0;
        g_Task->header.step  = g_Task->header.step + 1;
    }
}
#else
INCLUDE_ASM(func_801EF3DC);
#endif

INCLUDE_ASM(func_801EF4DC);

INCLUDE_ASM(func_801EF580);

MATCH void func_801EF690(void) {
    u8            counter;
    PartyBattler* work;

    g_Task->param.unk_0B += 4;
    work = g_Task;
    work->unk_10 += work->unk_1C;
    counter      = work->unk_09 - 1;
    work->unk_09 = counter;
    if (!(counter & 0xFF)) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF700(void) {
    u8            counter;
    s32           value;
    PartyBattler* work;

    g_Task->param.unk_0B += g_Task->timer >> 1;
    work         = g_Task;
    counter      = work->timer - 1;
    value        = work->unk_1C - 2;
    work->timer  = counter;
    work->unk_1C = value;
    work->unk_10 += value;
    if (!(counter & 0xFF)) {
        D_801EB4E0->param.unk_0B -= 1;
        func_801E5988();
    }
}

MATCH void func_801EF78C(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    if (BATTLE_ACTIVE_WORK->facing & 1) {
        rot.vx = 0;
        rot.vy = g_Task->unk_0C;
        rot.vz = 0;
    } else {
        rot.vx = g_Task->unk_0C;
        rot.vy = 0;
        rot.vz = 0;
    }
    BMAGIC_PROJECT_ACTOR_MATRIX(g_Task);
}

INCLUDE_ASM(func_801EF88C);

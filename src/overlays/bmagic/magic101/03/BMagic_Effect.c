#include "magic101_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC18(void) {
    BattleHandlerTable5 handlers;

    handlers = D_801EEC04;
    SYS_DISPATCH_BYTE(handlers.handlers, g_SpadWork->step_01);
    if (g_SpadWork->word_08.byte.timer_0A != 0 && g_SpadWork->flags_00 != 0) {
        Effect_SetActorMatrix();
        func_801EF07C();
        PopMatrix();
    }
}

/* Three shapes tried (if/else per branch, read-then-condition-xor, shared-goto): gcc's
 * cross-jump merges the g_BattleActingBattler tests or the facing reads (0x180 vs 0x19C);
 * retail keeps three separate D_8014637C loads and a shared xor block at 0x801EED50. First
 * diff 0x801EECE0, the side-mask test's target. Layout problem, not scheduling. */
#ifdef NON_MATCHING
NON_MATCHING void func_801EECCC(void) {
    u32 offset;
    u32 counter;
    u32 wave;
    u8  facing;

    if (g_BattleTargetSelector & 0x40) {
        if (g_BattleActingBattler >= BATTLE_PARTY_SLOT_COUNT) {
            facing = ((PartyBattler*)D_8014637C)->word_08.byte.facing_08;
            goto have_facing;
        }
    } else if (g_BattleActingBattler < BATTLE_PARTY_SLOT_COUNT) {
        facing = ((PartyBattler*)D_8014637C)->word_08.byte.facing_08;
        goto have_facing;
    }
    facing = ((PartyBattler*)D_8014637C)->word_08.byte.facing_08 ^ 0x2;
have_facing:
    g_SpadWork->word_08.byte.facing_08 = facing;
    func_800AFD9C();
    g_SpadWork->word_08.byte.unk_0B   = 0;
    g_SpadWork->word_08.byte.unk_09   = 0x30;
    g_SpadWork->word_08.byte.timer_0A = 0;
    g_SpadWork->step_01 += 1;
    counter = 0;
    do {
        offset                                   = (Battle_AllocEffect(1, 0x1B) & BYTE_MASK) * BATTLE_EFFECT_STRIDE;
        wave                                     = (counter >> 2) * 3;
        wave                                     = (wave << 2) + 1;
        FIELD(u8, D_801EC331, offset)            = 0;
        FIELD(u8, D_801EC334, offset)            = (u8)counter;
        FIELD(u8, D_801EC339, offset)            = (u8)wave;
        FIELD(PartyBattler*, D_801EC3A4, offset) = g_SpadWork;
        g_SpadWork->word_08.byte.unk_0B += 1;
        counter += 1;
    } while (counter < 0x10);
    SND_QueueSelectionFx(0x100);
}
#else
INCLUDE_ASM(func_801EECCC);
#endif

MATCH void func_801EEE68(void) {
    u8 timer;

    timer                             = g_SpadWork->word_08.byte.timer_0A + 1;
    g_SpadWork->word_08.byte.timer_0A = timer;
    if (timer == 16) {
        func_800A9610(g_BattleTargetSelector, 0x10);
        g_SpadWork->step_01 = g_SpadWork->step_01 + 1;
    }
}

#include "overlays/bmagic/Effect_CountDownTimerNextStep.h"

MATCH void func_801EEF20(void) {
    u8 timer;

    timer                             = g_SpadWork->word_08.byte.timer_0A - 1;
    g_SpadWork->word_08.byte.timer_0A = timer;
    if (timer == 0) {
        g_SpadWork->step_01 = g_SpadWork->step_01 + 1;
    }
}

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801EF07C);

MATCH void func_801EF310(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_SpadWork->step_01);
}

MATCH void func_801EF354(void) {
    SYS_DISPATCH_BYTE(D_801EFCE8, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
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

    counter                         = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = counter;
    if (!(counter & 0xFF)) {
        g_SpadWork->word_08.byte.facing_08 = D_801EB4E0->word_08.byte.facing_08;
        g_SpadWork->coord_x_34.raw         = D_801EB4E0->coord_x_34.raw;
        angle                              = g_SpadWork->unk_04;
        g_SpadWork->coord_y_38.raw         = D_801EB4E0->coord_y_38.raw;
        g_SpadWork->word_08.byte.unk_0B    = angle * 4 & 0x3F;
        g_SpadWork->word_3C.word           = D_801EB4E0->word_3C.word + 0x01800000;
        value                              = D_801EFCC0[g_SpadWork->unk_04];
        g_SpadWork->unk_10                 = 0x60;
        angle                              = g_SpadWork->unk_04;
        g_SpadWork->unk_14                 = 0x20;
        g_SpadWork->word_08.byte.unk_09    = angle * 4 + 1;
        g_SpadWork->unk_0C                 = value << 8;
        g_SpadWork->word_08.byte.timer_0A  = 0;
        g_SpadWork->unk_02                 = g_SpadWork->unk_02 + 1;
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

    g_SpadWork->word_08.byte.unk_0B += 4;
    work = g_SpadWork;
    work->unk_10 += work->unk_1C;
    counter                   = work->word_08.byte.unk_09 - 1;
    work->word_08.byte.unk_09 = counter;
    if (!(counter & 0xFF)) {
        g_SpadWork->unk_02 += 1;
    }
}

MATCH void func_801EF700(void) {
    u8            counter;
    s32           value;
    PartyBattler* work;

    g_SpadWork->word_08.byte.unk_0B += g_SpadWork->word_08.byte.timer_0A >> 1;
    work                        = g_SpadWork;
    counter                     = work->word_08.byte.timer_0A - 1;
    value                       = work->unk_1C - 2;
    work->word_08.byte.timer_0A = counter;
    work->unk_1C                = value;
    work->unk_10 += value;
    if (!(counter & 0xFF)) {
        D_801EB4E0->word_08.byte.unk_0B -= 1;
        func_801E5988();
    }
}

MATCH void func_801EF78C(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    if (BATTLE_ACTIVE_WORK->word_08.byte.facing_08 & 1) {
        rot.vx = 0;
        rot.vy = g_SpadWork->unk_0C;
        rot.vz = 0;
    } else {
        rot.vx = g_SpadWork->unk_0C;
        rot.vy = 0;
        rot.vz = 0;
    }
    BMAGIC_PROJECT_ACTOR_MATRIX(g_SpadWork);
}

INCLUDE_ASM(func_801EF88C);

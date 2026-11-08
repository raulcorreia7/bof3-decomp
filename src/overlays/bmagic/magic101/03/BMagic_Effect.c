#include "magic101_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC18(void) {
    Magic101Steps handlers;

    handlers = D_801EEC04;
    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.mode);
    if (g_Task->timer != 0 && g_Task->header.flags != 0) {
        Effect_SetActorMatrix();
        func_801EF07C();
        PopMatrix();
    }
}

/* Three shapes tried (if/else per branch, read-then-condition-xor, shared-goto): gcc's
 * cross-jump merges the g_Battle.active_battler tests or the facing reads (0x180 vs 0x19C);
 * retail keeps three separate D_8014637C loads and a shared xor block at 0x801EED50. First
 * diff 0x801EECE0, the side-mask test's target. Layout problem, not scheduling. */
#ifdef NON_MATCHING
NON_MATCHING void func_801EECCC(void) {
    u32 slot;
    u32 counter;
    u32 wave;
    u8  facing;

    if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
        if (g_Battle.active_battler >= BATTLE_PARTY_CHARACTERS_COUNT) {
            facing = ((PartyMember*)D_8014637C)->facing;
            goto have_facing;
        }
    } else if (g_Battle.active_battler < BATTLE_PARTY_CHARACTERS_COUNT) {
        facing = ((PartyMember*)D_8014637C)->facing;
        goto have_facing;
    }
    facing = ((PartyMember*)D_8014637C)->facing ^ 0x2;
have_facing:
    g_Task->facing = facing;
    func_800AFD9C();
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 0x30;
    g_Task->timer        = 0;
    g_Task->header.mode += 1;
    counter = 0;
    do {
        slot                               = Battle_AllocEffect(1, 0x1B) & BYTE_MASK;
        wave                               = (counter >> 2) * 3;
        wave                               = (wave << 2) + 1;
        g_BattleEffects[slot].header.mode  = 0;
        g_BattleEffects[slot].unk_04       = counter;
        g_BattleEffects[slot].arg.unk_09   = wave;
        g_BattleEffects[slot].target.party = g_Task;
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
        func_800A9610(g_Battle.target_selector, 0x10);
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
    SYS_DISPATCH_BYTE(g_BMagicEffectModes, g_Task->header.mode);
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
        g_Task->facing       = g_BattleEffectBattler->facing;
        g_Task->pos.x.fixed  = g_BattleEffectBattler->pos.x.fixed;
        angle                = g_Task->unk_04;
        g_Task->pos.y.fixed  = g_BattleEffectBattler->pos.y.fixed;
        g_Task->param.unk_0B = angle * 4 & 0x3F;
        g_Task->pos.z.fixed  = g_BattleEffectBattler->pos.z.fixed + 0x01800000;
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

/* Blocker: retail reloads g_Task after the rsin shift (sll v0,v0,5 at 0x801EF514); the candidate hoists the g_Task load above it. Three drafts (local work, direct reads, split offset) all fail there. */
INCLUDE_ASM(func_801EF4DC);

// hint: front half matches (wave local, count local); retail stores unk_10/unk_14 = 0x80 before unk_09 = 0x10 and does sw unk_1C through the old task pointer, but the candidate hoists li 16/sb unk_09 first
INCLUDE_ASM(func_801EF580);

MATCH void func_801EF690(void) {
    u8           counter;
    PartyMember* work;

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
    u8           counter;
    s32          value;
    PartyMember* work;

    g_Task->param.unk_0B += g_Task->timer >> 1;
    work         = g_Task;
    counter      = work->timer - 1;
    value        = work->unk_1C - 2;
    work->timer  = counter;
    work->unk_1C = value;
    work->unk_10 += value;
    if (!(counter & 0xFF)) {
        g_BattleEffectBattler->param.unk_0B -= 1;
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

#ifndef OVERLAY_BMAGIC_MAGIC099_03_H
#define OVERLAY_BMAGIC_MAGIC099_03_H

/* The bmagic/magic099/03 overlay. Only this image includes the file. */

/* The scratchpad base here is the 32-bit depth word. */
#define GAME_SCRATCH_BASE_WORD

#include "overlays/bmagic/bmagic.h"
#include "overlays/battle/battle/15/battle_15.h"
#include "slus/functions.h"

extern s32 D_1F800004;

/* The bolt's first segment length, and the flicker of the later ones: base plus or minus a random part. */
#define BOLT_RADIUS       0x40
#define BOLT_FLICKER_MASK 0x3F
#define BOLT_FLICKER_BASE 0x80

/* The bolt point D_1F800014, also read as halfwords, and the scratch words of the bolt: the segment length, the
 * swing angle, the flicker and the segment count. */
extern SVECTOR             D_1F800014[];
extern s16                 D_1F800014_HALF[];
extern s16                 D_1F800016;
extern s16                 D_1F800018;
extern s32                 D_1F800008;
extern s32                 D_1F80000C;
extern Magic068SharedSteps D_801EEC04;
extern Callback            D_801F09A0[4];
extern Callback            D_801F09B0[4];
extern Callback            D_801F09C0[4];

/* Advance the effect timer: one step of the counter, reloading the work cell on
 * every store. */
static inline void BattleEffectTimerStep(void) {
    PartyMember* work;

    /* A store through the pointer may alias the cell, so each step reloads
     * it. */
    g_Task->param.unk_0B++;
    work = g_Task;
    if (work->timer < 16) {
        work->timer += 2;
    } else {
        work->unk_09 = 60;
        work         = g_Task;
        work->header.step++;
    }
}

/* Orbit projection step: advance the orbit counter, store the angle and its
 * depth in the scratchpad pair, then add the cos/sin velocities to the
 * projected position. */
static inline void MagicOrbitProjectionStep(s32 depth) {
    PartyMember* work;
    s32          counter;
    s32          angle;
    /* FAKE: retail keeps the angle cell in $s0 across both scratchpad stores;
     * without the pin GCC rematerialises its address and the function measured
     * 0x8 short. */
    FAKE_REG(s32*, angle_cell, "s0");
    s32 velocity;

    g_Task->param.unk_0B++;

    work                   = g_Task;
    counter                = work->unk_0C + 1;
    VOL(s32, work->unk_0C) = counter;
    angle                  = (counter & 0x7F) << 5;
    angle_cell             = &D_1F800004;
    *angle_cell            = angle;
    D_1F800000             = depth;

    velocity          = rcos(angle) * D_1F800000;
    work              = g_Task;
    work->pos.x.fixed = BATTLE_ACTIVE_WORK->pos.x.fixed + velocity;

    velocity            = rsin(*angle_cell) * D_1F800000;
    g_Task->pos.y.fixed = BATTLE_ACTIVE_WORK->pos.y.fixed + velocity;

    if (--g_Task->unk_09 == 0) {
        g_Task->header.step++;
    }
}

void func_801EF8F0(s32 arg0, s32 arg1, s16 arg2);
/* func_801F043C */
void func_801F070C(void);

#endif

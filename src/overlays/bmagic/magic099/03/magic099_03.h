#ifndef OVERLAY_BMAGIC_MAGIC099_03_H
#define OVERLAY_BMAGIC_MAGIC099_03_H

/* The bmagic/magic099/03 overlay. Only this image includes the file. */

/* The scratchpad base here is the 32-bit depth word. */
#define GAME_SCRATCH_BASE_WORD

#include "overlays/bmagic/bmagic.h"
#include "overlays/battle/battle/15/battle_15.h"

extern s32                 D_1F800004;
extern BattleHandlerTable5 D_801EEC04;
extern Callback            D_801F09A0[4];
extern Callback            D_801F09B0[4];
extern Callback            D_801F09C0[4];

/* Advance the effect timer: one step of the counter, reloading the work cell on
 * every store. */
static inline void BattleEffectTimerStep(void) {
    PartyBattler* work;

    /* A store through the pointer may alias the cell, so each step reloads
     * it. */
    g_SpadWork->word_08.byte.unk_0B++;
    work = g_SpadWork;
    if (work->word_08.byte.unk_0A < 16) {
        work->word_08.byte.unk_0A += 2;
    } else {
        work->word_08.byte.unk_09 = 60;
        work                      = g_SpadWork;
        work->unk_02++;
    }
}

/* Orbit projection step: advance the orbit counter, store the angle and its
 * depth in the scratchpad pair, then add the cos/sin velocities to the
 * projected position. */
static inline void MagicOrbitProjectionStep(s32 depth) {
    PartyBattler* work;
    s32           counter;
    s32           angle;
    /* FAKE: retail keeps the angle cell in $s0 across both scratchpad stores;
     * without the pin GCC rematerialises its address and the function measured
     * 0x8 short. */
    MATCH_REG(s32*, angle_cell, "s0");
    s32 velocity;

    g_SpadWork->word_08.byte.unk_0B++;

    work                   = g_SpadWork;
    counter                = work->unk_0C + 1;
    VOL(s32, work->unk_0C) = counter;
    angle                  = (counter & 0x7F) << 5;
    angle_cell             = &D_1F800004;
    *angle_cell            = angle;
    D_1F800000             = depth;

    velocity             = rcos(angle) * D_1F800000;
    work                 = g_SpadWork;
    work->coord_x_34.raw = BATTLE_ACTIVE_WORK->coord_x_34.raw + velocity;

    velocity                   = rsin(*angle_cell) * D_1F800000;
    g_SpadWork->coord_y_38.raw = BATTLE_ACTIVE_WORK->coord_y_38.raw + velocity;

    if (--g_SpadWork->word_08.byte.unk_09 == 0) {
        g_SpadWork->unk_02++;
    }
}

void func_801F043C(void);
void func_801EF8F0(s32 arg0, s32 arg1, s16 arg2);
void func_801F070C(void);

#endif

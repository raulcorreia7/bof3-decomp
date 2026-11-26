#ifndef OVERLAY_BMAGIC_MAGIC099_03_H
#define OVERLAY_BMAGIC_MAGIC099_03_H

/* The bmagic/magic099/03 overlay. Only this image includes the file. */

/* The scratchpad base here is the 32-bit depth word. */
#define FAKE_DECL_GAME_SCRATCH_BASE_WORD

#include "overlays/bmagic/bmagic.h"
#include "overlays/battle/battle/15/battle_15.h"
#include "slus/functions.h"

extern s32 D_1F800004;

/* The bolt's first segment length, and the flicker of the later ones: base plus or minus a random part. */
#define BOLT_RADIUS       0x40
#define BOLT_FLICKER_MASK 0x3F
#define BOLT_FLICKER_BASE 0x80
#define BOLT_FLICKER_CELL g_ScratchPad

/* The bolt point g_ScratchPadVectors, also read as halfwords, and the scratch words of the bolt: the segment length, the
 * swing angle, the flicker and the segment count. */
extern s32           D_1F800008;
extern s32           D_1F80000C;
extern Magic068Steps D_801EEC04;
extern Callback      D_801F09A0[4];
extern Callback      D_801F09B0[4];
extern Callback      D_801F09C0[4];

/* Advance the effect timer: one step of the counter, reloading the work cell on
 * every store. */
static inline void BattleEffectTimerStep(void) {
    PartyMember* work;

    /* A store through the pointer may alias the cell, so each step reloads
     * it. */
    SELF(PartyMember)->param.unk_0B++;
    work = SELF(PartyMember);
    if (work->timer < 16) {
        work->timer += 2;
    } else {
        work->unk_09 = 60;
        work         = SELF(PartyMember);
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

    SELF(PartyMember)->param.unk_0B++;

    work                             = SELF(PartyMember);
    counter                          = work->unk_0C + 1;
    FAKE_VOLATILE(s32, work->unk_0C) = counter;
    angle                            = (counter & 0x7F) << 5;
    angle_cell                       = &D_1F800004;
    *angle_cell                      = angle;
    g_ScratchPad                     = depth;

    velocity          = rcos(angle) * g_ScratchPad;
    work              = SELF(PartyMember);
    work->pos.x.fixed = BATTLE_ACTIVE_WORK->pos.x.fixed + velocity;

    velocity                       = rsin(*angle_cell) * g_ScratchPad;
    SELF(PartyMember)->pos.y.fixed = BATTLE_ACTIVE_WORK->pos.y.fixed + velocity;

    if (--SELF(PartyMember)->unk_09 == 0) {
        SELF(PartyMember)->header.step++;
    }
}

void func_801EF8F0(s16 band_height, s16 radius, s16 jitter_mask);
/* func_801F043C */
void func_801F070C(void);

#endif

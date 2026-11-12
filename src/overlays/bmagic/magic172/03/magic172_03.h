#ifndef OVERLAY_BMAGIC_MAGIC172_03_H
#define OVERLAY_BMAGIC_MAGIC172_03_H

/* The bmagic/magic172/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* The effect timer drops by 2 per tick. */
#define EFFECT_TIMER_TICK 2

extern Callback D_801F0B90[];

void func_800AF3A0(VECTOR pos, s16 step);
void func_801EEDD8(void);
void func_801F0908(void);

#endif

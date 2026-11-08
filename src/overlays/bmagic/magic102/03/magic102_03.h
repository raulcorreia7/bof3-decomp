#ifndef OVERLAY_BMAGIC_MAGIC102_03_H
#define OVERLAY_BMAGIC_MAGIC102_03_H

/* The bmagic/magic102/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"
#include "slus/exports.h"
#include "slus/functions.h"
#include "slus/part.h"

extern SVECTOR D_1F800014[];
/* D_1F800034 read unsigned: the screen x and y RotTransPers writes. */
extern u16     D_1F800034_U16[2];

s32 func_801F0ADC(s32 x, s32 y);

extern EffectStepFuncs4 D_801EEC04;

/* This effect steps the shared tick counter (unk_09) by one per
 * step and advances the magic step at its limit. */
#define EFFECT_TICK_INCREMENT 1
#define EFFECT_TICK_LIMIT     0x10

#endif

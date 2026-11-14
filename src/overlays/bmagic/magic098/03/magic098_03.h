#ifndef OVERLAY_BMAGIC_MAGIC098_03_H
#define OVERLAY_BMAGIC_MAGIC098_03_H

/* The bmagic/magic098/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* The scratch words D_1F800000 read as halfwords: the bolt radius, angle, flicker and segment count. */
extern s16 D_1F800000_HALF[];
extern s16 D_1F800002;
extern s16 D_1F800004;
extern s16 D_1F800008;
/* The bolt point D_1F800014, also read as halfwords. */
extern s16 D_1F800014_HALF[];
extern s16 D_1F800016;
extern s16 D_1F800018;

void func_801EF5D4(s16 band_height, u16 radius, u16 jitter_mask);
void func_801EFE24(void);
void func_801F00C4(void);

#endif

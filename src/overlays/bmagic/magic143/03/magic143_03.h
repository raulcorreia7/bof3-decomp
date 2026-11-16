#ifndef OVERLAY_BMAGIC_MAGIC143_03_H
#define OVERLAY_BMAGIC_MAGIC143_03_H

/* The bmagic/magic143/03 overlay. Only this image includes the file. */

/* The scratchpad base here is the 32-bit depth word. */

#include "overlays/bmagic/bmagic.h"
#include "slus/functions.h"

/* The bolt's first segment length, and the flicker of the later ones: base plus or minus a random part. */
#define BOLT_RADIUS       0x80
#define BOLT_FLICKER_MASK 0x1F
#define BOLT_FLICKER_BASE 0xA0
#define BOLT_FLICKER_CELL g_ScratchPad.cells.words[0]

/* The bolt point g_ScratchPadVectors, also read as halfwords, and the scratch words of the bolt: the segment length, the
 * swing angle, the flicker and the segment count. */
extern s32 D_1F800008;
extern s32 D_1F80000C;
extern s32 D_1F800004;

void func_801EED24(void);
void func_801EF23C(s32 band_height, u16 radius, u16 jitter_mask);
void func_801EFC74(void);

#endif

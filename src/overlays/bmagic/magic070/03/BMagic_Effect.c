#include "magic070_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC28_2.h"

#include "overlays/bmagic/func_801EED38.h"

#include "overlays/bmagic/Effect_ReplacePaletteFade.h"

#include "overlays/bmagic/Effect_BrightenPalette.h"

#include "overlays/bmagic/Effect_NextStep.h"

#include "overlays/bmagic/func_801EF1A4.h"

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

#include "overlays/bmagic/func_801EF33C.h"

#include "overlays/bmagic/func_801EF380.h"

#include "overlays/bmagic/func_801EF47C.h"

#include "overlays/bmagic/func_801EF67C.h"

#include "overlays/bmagic/func_801EF72C.h"

/* Tried a struct view of the scratch block at 0x1F800000 (x, y, radius, angle, red, green, blue, rim),
 * by constant, by D_1F800000 and by a pointer local. Retail holds 0x1F800008 in a1 from the red store
 * and bases the loop on a1 - 2 and a1 - 8; ours uses constant addresses: sw ra 0x30 for 0x34. */
INCLUDE_ASM(func_801EF810);

/* The three-point twin of func_801EF810, with the same scratch-base difference: addiu sp -0x38 for
 * -0x40. The loop bound is recomputed on each pass and the first test is the constant 1. */
INCLUDE_ASM(func_801EFA44);

/* An angle local (i << 9 kept per pass, not strength-reduced) gives the retail frame. Retail then holds
 * &radius (0x1F800004) in a2 from the radius store and bases the loop on a2 - 4; a pointer local bases
 * it on x: move s3,zero for s2. */
INCLUDE_ASM(func_801EFCDC);

#include "overlays/bmagic/func_801F0000.h"

#include "overlays/bmagic/func_801F006C.h"

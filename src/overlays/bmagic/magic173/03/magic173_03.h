#ifndef OVERLAY_BMAGIC_MAGIC173_03_H
#define OVERLAY_BMAGIC_MAGIC173_03_H

/* The bmagic/magic173/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* The effect timer drops by 4 per tick. */
#define EFFECT_TIMER_TICK 4

/* D_801F09B0 */
extern TrailPoint BMagic_Trail[][BMAGIC_TRAIL_LENGTH];
extern Callback   D_801F0990[];
extern Callback   D_801F09A0[];

void func_801EED90(void);
void func_800AF3A0(VECTOR pos, s16 step);
/* func_801F02B0 */
/* func_801F03A0 */

#endif

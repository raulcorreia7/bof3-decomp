#ifndef SHARED_BMAGIC_RING_H
#define SHARED_BMAGIC_RING_H

/* The ring effect of magic055 (Ebonfire) and magic091 (Flare). */

#include "overlays/bmagic/bmagic.h"

/* The ring bands the task starts. */
#define BMAGIC_RING_COUNT             6
/* The start delay of the first ring band, and how much longer each later one waits, in frames. */
#define BMAGIC_RING_FIRST_DELAY       1
#define BMAGIC_RING_STAGGER           6
/* The radius step at which the task's disc stops growing. */
#define BMAGIC_RING_EXPAND_LIMIT      0x10
/* The radius step a ring band starts from, and the one at which it stops shrinking fast. */
#define BMAGIC_RING_BAND_RADIUS       0x40
#define BMAGIC_RING_BAND_SHRINK_LIMIT 0x10

/* D_801EEC04 */
extern BMagicActorSteps g_BMagicRingModes;
/* D_801EFC64 */
extern Callback         g_BMagicRingBandModes[];

/* func_801EF240 */
void BMagic_RingBandDraw(void);
/* func_801EF7B0 */
void BMagic_RingDrawDisc(void);
/* func_801EF9E4 */
void BMagic_RingDrawShade(void);

#endif

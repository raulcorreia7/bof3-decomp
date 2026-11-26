#ifndef OVERLAY_BMAGIC_MAGIC042_03_H
#define OVERLAY_BMAGIC_MAGIC042_03_H

/* The bmagic/magic042/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* func_801EEC70 */
void BMagic_BurstInit(void);

/* The steps of the flare effect. */
#define BMAGIC_BURST_FLARE_STEP_COUNT 5

typedef struct BMagicBurstFlareSteps {
    Callback steps[BMAGIC_BURST_FLARE_STEP_COUNT];
} BMagicBurstFlareSteps;

/* D_801EEC04 */
extern BMagicBurstFlareSteps g_BMagicBurstFlareSteps;
/* D_801EFB74 */
extern Pos2                  g_BMagicBurstCharacterOffsets[][2];
/* D_801EFBCC */
extern Pos2                  g_BMagicBurstFormOffsets[][2];
/* D_801EFC24 */
extern u8                    g_BMagicBurstFormTypes[];
/* func_801EF380 */
void                         BMagic_BurstDrawRays(u8 start, u16 radius);
/* func_801EF71C */
void                         BMagic_BurstDrawSpokes(u8 start, u16 radius);
/* func_801EF920 */
void                         BMagic_BurstDrawGlow(void);

#endif

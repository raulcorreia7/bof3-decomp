#ifndef OVERLAY_BMAGIC_MAGIC056_03_H
#define OVERLAY_BMAGIC_MAGIC056_03_H

/* The bmagic/magic056/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* The effects the task starts: header.mode picks the routine g_BMagicEffectModes runs; mode 1 runs the dome too. */
typedef enum BMagicSacrificeEffectMode {
    BMAGIC_SACRIFICE_EFFECT_DOME   = 0,
    BMAGIC_SACRIFICE_EFFECT_SHADOW = 2,
    BMAGIC_SACRIFICE_EFFECT_CLONE  = 3
} BMagicSacrificeEffectMode;

/* The steps of the clone effect. */
#define BMAGIC_SACRIFICE_CLONE_STEP_COUNT 9

typedef struct BMagicSacrificeCloneSteps {
    Callback steps[BMAGIC_SACRIFICE_CLONE_STEP_COUNT];
} BMagicSacrificeCloneSteps;

/* D_801EEC10 */
extern BMagicSacrificeCloneSteps g_BMagicSacrificeCloneSteps;
/* D_801F0754 */
extern Callback                  g_BMagicSacrificeDomeSteps[];
/* func_801EF4C0 */
void                             BMagic_SacrificeDrawDome(void);
/* func_800AFB48 */
u8                               Battle_CopyCellPalette(PartyMember* battler);

/* D_801F0760 */
extern Callback g_BMagicSacrificeShadowSteps[];
/* func_801EFC74 */
void            BMagic_SacrificeDrawShadow(void);

#endif

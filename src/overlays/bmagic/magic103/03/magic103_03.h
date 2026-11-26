#ifndef OVERLAY_BMAGIC_MAGIC103_03_H
#define OVERLAY_BMAGIC_MAGIC103_03_H

/* The bmagic/magic103/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* The effects the task starts: header.mode picks the handler g_BMagicEffectModes runs. */
typedef enum BMagicSimoonEffectMode {
    BMAGIC_SIMOON_EFFECT_DOME   = 0,
    BMAGIC_SIMOON_EFFECT_GLOW   = 1,
    BMAGIC_SIMOON_EFFECT_SHADOW = 2
} BMagicSimoonEffectMode;

/* D_801F07A0 */
extern Callback g_BMagicSimoonDomeSteps[];
/* D_801F07AC */
extern Pos3     g_BMagicSimoonGlowOffsets[];

/* D_801F07C4 */
extern Callback g_BMagicSimoonGlowSteps[];
/* func_801EF1D8 */
void            BMagic_SimoonDrawDome(void);

/* func_801EFE20 */
void BMagic_SimoonDrawGlow(void);

/* D_801F07D4 */
extern Callback g_BMagicSimoonShadowSteps[];
/* func_801F04E0 */
void            BMagic_SimoonDrawShadow(void);

#endif

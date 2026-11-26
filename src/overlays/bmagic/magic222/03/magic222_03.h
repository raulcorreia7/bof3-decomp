#ifndef OVERLAY_BMAGIC_MAGIC222_03_H
#define OVERLAY_BMAGIC_MAGIC222_03_H

/* The bmagic/magic222/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern s16      D_1F800004;
extern u16      D_1F80000A;
/* D_801F0D64 */
extern Callback g_BMagicCombustionActorSteps[];
/* D_801F0D7C */
extern Callback g_BMagicCombustionShadowSteps[];

/* D_801F0D8C */
extern Callback g_BMagicCombustionSparkSteps[];
/* func_801F0168 */
void            Effect_SetActorMatrix3(void);
/* func_801F0218 */
void            BMagic_CombustionDrawSpark(void);

/* D_801F0D98 */
extern Callback g_BMagicCombustionWaveSteps[];

#endif

#ifndef OVERLAY_BMAGIC_MAGIC118_03_H
#define OVERLAY_BMAGIC_MAGIC118_03_H

/* The bmagic/magic118/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

#define MAGIC118_STEP_COUNT 5

typedef struct Magic118Steps {
    Callback steps[MAGIC118_STEP_COUNT];
} Magic118Steps;

extern Magic118Steps D_801EEC04;
extern Callback      D_801EFCD4[];

/* func_801EF194 */
void BMagic_DrawBurnSprites(void);

/* func_801EF6BC */
extern SVECTOR D_1F800014[];
void           BMagic_DrawBurnFlameQuads(void);
/* func_801EFA1C */
void           BMagic_DrawBurnFlameTris(void);

#endif

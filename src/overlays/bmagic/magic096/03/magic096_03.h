#ifndef OVERLAY_BMAGIC_MAGIC096_03_H
#define OVERLAY_BMAGIC_MAGIC096_03_H

/* The bmagic/magic096/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern SVECTOR D_1F800014[];
void           BMagic_DrawGlowRing(void);
void           func_801F0164(void);

#define MAGIC096_STEP_COUNT 5

typedef struct Magic096Steps {
    Callback steps[MAGIC096_STEP_COUNT];
} Magic096Steps;

extern Magic096Steps D_801EEC10;
extern u8            D_801F0488[];
/* One byte per spawned effect. */
extern u8            D_801F0498[];

#endif

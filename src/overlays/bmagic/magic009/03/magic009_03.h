#ifndef OVERLAY_BMAGIC_MAGIC009_03_H
#define OVERLAY_BMAGIC_MAGIC009_03_H

/* The bmagic/magic009/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* The timer reloads from the second table. */
#define EFFECT_TIMER_RELOAD func_800B0058

extern Magic004SharedSteps D_801EEC04;

#define MAGIC009_STEP_COUNT 4

typedef struct Magic009Steps {
    Callback steps[MAGIC009_STEP_COUNT];
} Magic009Steps;

extern Magic009Steps D_801EEC18;
extern Callback      D_801EF8A4[];
/* The per-ticker position offset func_801EF198 adds to the selected actor: x,
 * y and z in 16.16. */
extern Point3DL      D_801EF8B0[];

void func_801EF3B8(void);

#endif

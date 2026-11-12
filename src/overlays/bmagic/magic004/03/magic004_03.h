#ifndef OVERLAY_BMAGIC_MAGIC004_03_H
#define OVERLAY_BMAGIC_MAGIC004_03_H

/* The bmagic/magic004/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern Magic004SharedSteps D_801EEC04;

#define MAGIC004_STEP_COUNT 4

typedef struct Magic004Steps {
    Callback steps[MAGIC004_STEP_COUNT];
} Magic004Steps;

extern Magic004Steps D_801EEC18;
extern u8            D_801EFE34[];
extern u16           D_801EFE40[];

/* D_801EFE60 */
extern Callback BMagic_StepTable[];

#endif

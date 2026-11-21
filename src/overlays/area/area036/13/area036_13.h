#ifndef OVERLAY_WORLD00_AREA036_13_H
#define OVERLAY_WORLD00_AREA036_13_H

/* The world00/area036/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/worlds/world00.h"

/* Step tables the step bytes selects. */
extern void (*D_801F3304[])(void);

/* The scratchpad work object's loader hook. */
/* Drains the copied position against the image's wall list. */
void Area_DrawLightPillar(s32* pos);

/* The first row of the trigger band in the shared Area_TestStepTrigger body. */

#endif

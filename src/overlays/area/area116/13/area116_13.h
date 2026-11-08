#ifndef OVERLAY_WORLD03_AREA116_13_H
#define OVERLAY_WORLD03_AREA116_13_H

/* The world03/area116/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world03.h"
#include "work/area_spad.h"

extern Callback D_801F34E8[];

void Area_DrawLightPillar(s32* pos);

/* The first row of the trigger band in the shared Area_CheckStepTrigger body. */
#define AREA_STEP_TRIGGER_ROW 0x33

#endif

#ifndef OVERLAY_WORLD03_AREA116_13_H
#define OVERLAY_WORLD03_AREA116_13_H

/* The world03/area116/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world03.h"
#include "work/area_spad.h"

extern Callback D_801F34E8[];

void GFX_FreePaletteFadeTarget(void* target);
void func_801F2F78(s32 pos[3]);

/* func_801F2DB4 */
s32 Area_CheckStepTrigger(s32 x, s32 y);

/* The first row of the trigger band in the shared Area_CheckStepTrigger body. */
#define AREA_STEP_TRIGGER_ROW 0x33

#endif

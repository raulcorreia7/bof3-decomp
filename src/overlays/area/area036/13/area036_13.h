#ifndef OVERLAY_WORLD00_AREA036_13_H
#define OVERLAY_WORLD00_AREA036_13_H

/* The world00/area036/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world00.h"

/* Handler table the step byte selects. */
extern void (*D_801F3304[])(void);

/* The scratchpad work object's loader hook. */
/* func_80196718 */
void GFX_FreePaletteFadeTarget(void* target);
/* Drains the copied position against the image's wall list. */
void func_801F2DF0(s32* pos);

/* func_801F2C64 */
s32 Area_CheckStepTrigger(s32 x, s32 y);

/* The first row of the trigger band in the shared Area_CheckStepTrigger body. */
#define AREA_STEP_TRIGGER_ROW 0x23

#endif

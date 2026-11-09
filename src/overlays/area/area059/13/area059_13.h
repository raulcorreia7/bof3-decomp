#ifndef OVERLAY_WORLD01_AREA059_13_H
#define OVERLAY_WORLD01_AREA059_13_H

/* The world01/area059/13 overlay: one file per split function and its data. */

#include "overlays/area/world01.h"

/* The script copy points at an Actor row of g_Actors. */
#define g_ScriptWorkRecord ((Actor*)g_ScriptWorkRecord)

extern u8 D_801F3824[];

void Area_DrawLightPillar(s32* pos);

/* The first row of the trigger band in the shared Area_CheckStepTrigger body. */

#endif

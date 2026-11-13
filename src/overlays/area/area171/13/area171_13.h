#ifndef OVERLAY_WORLD04_AREA171_13_H
#define OVERLAY_WORLD04_AREA171_13_H

/* The world04/area171/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world04.h"
#include "area/spad.h"

/* The scratchpad cell holding this mode's work pointer. */

/* The payload's per-state handler table. */
extern u8         D_801F3F5C[];
extern TriggerBox D_801F4188[2];

extern u8 D_80144CAA;

/* The quad's blue level by step, in units of 8. */
extern u8 D_801F3F88[];
void      func_801A4BC0(s32 arg0, s32 arg1, s32 arg2);
void      func_801F3070(s32 mode);

#endif

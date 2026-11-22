#ifndef OVERLAY_WORLD04_AREA171_13_H
#define OVERLAY_WORLD04_AREA171_13_H

/* The world04/area171/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/worlds/world04.h"
extern u8 D_80144CAA;

/* The scratchpad cell holding this mode's work pointer. */

/* The payload's per-state handler table. */
extern u8 D_801F3F5C[];

/* The signed step scale the quad's height sample uses. */
extern u8         D_801F3F84[];
/* The quad's blue level by step, in units of 8. */
extern u8         D_801F3F88[];
extern TriggerBox D_801F4188[2];
void              func_801A4BC0(s32 column, s32 row, s32 code);
void              func_801F3070(s32 mode);
/* The work bound lookup of the party row's trigger box. */
u8                func_801F379C(u8 member);
/* The resident field-step helpers the party sync calls. */
void              func_801F3868(void);

#endif

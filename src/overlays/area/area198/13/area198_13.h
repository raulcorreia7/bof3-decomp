#ifndef OVERLAY_WORLD04_AREA198_13_H
#define OVERLAY_WORLD04_AREA198_13_H

/* The world04/area198/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world04.h"
#include "area/spad.h"

/* The scene state byte the update gates on. */
/* The global state byte this entry tests. */
/* The object pointer whose palette field this entry updates. */

/* The current map row in the field-loader table. */
/* The scratchpad work pointer the palette pass reads. */
/* The state handler banks the step dispatchers index. */
extern u8       D_801F3DFC[];
/* The setup callback table. */
extern Callback D_801F4324[17];
/* The palette source bytes passed to the slot claim. */
extern u8       D_801F4368[];

void            Actor_BeginScript(u8 script_index, u16 position);
extern Callback D_801F43EC[];

/* The state update's fallback handler. */
/* The image's setup pass. */
void func_801F2D28(s32 arg0);

#endif

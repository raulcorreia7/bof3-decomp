#ifndef OVERLAY_WORLD02_AREA100_13_H
#define OVERLAY_WORLD02_AREA100_13_H

/* The world02/area100/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/worlds/world02.h"

extern u8  D_801F407C[];
extern u8  D_801F4084[];
extern u16 D_801F4F5C[];
extern u8  D_801F4F68[];

void Area_DrawMatrixLightPillar(s32* pos);
void func_801F31E8(Pos3* pos, s32 height);
void Area_DrawLightPillar(s32* pos);

#endif

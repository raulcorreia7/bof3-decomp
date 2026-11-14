#ifndef OVERLAY_WORLD02_AREA100_13_H
#define OVERLAY_WORLD02_AREA100_13_H

/* The world02/area100/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world02.h"
#include "area/spad.h"

extern u8  D_801F407C[];
extern u8  D_801F4084[];
extern u8  D_801F4F68[];
extern u16 D_801F4F5C[];

void func_801F2D60(void*);
void func_801F31E8(Point3l* pos, s32 height);
void Area_DrawLightPillar(s32* pos);

#endif

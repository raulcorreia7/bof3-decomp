#ifndef OVERLAY_WORLD02_AREA100_13_H
#define OVERLAY_WORLD02_AREA100_13_H

/* The world02/area100/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world02.h"
#include "work/area_spad.h"

extern u8 D_801F407C[];
extern u8 D_801F4084[];
extern u8 D_801F4F68[];

void GFX_FreePaletteFadeTarget(void* target);
void func_801F2D60(void*);
void func_801F31E8(Vec3i* pos, s32 vz);
void func_801F3D70(void*);

#endif

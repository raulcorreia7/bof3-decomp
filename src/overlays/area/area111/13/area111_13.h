#ifndef OVERLAY_WORLD02_AREA111_13_H
#define OVERLAY_WORLD02_AREA111_13_H

/* The world02/area111/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world02.h"
#include "area/spad.h"

extern SVECTOR D_1F800014[];
extern Actor   D_80147A58[];
extern u8      D_801F4890[];
extern u8      D_801F489C[];
/* g_SceneEventStep read unsigned: func_801F3EE8 switches on a byte load. */
extern u8      g_SceneEventStep_u8[];

void func_801F2DA0(void* arg0, s32 arg1, s32 arg2);

void func_801A4BC0(s32 arg0, s32 arg1, s32 arg2);

#endif

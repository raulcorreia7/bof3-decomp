#ifndef OVERLAY_WORLD03_AREA119_13_H
#define OVERLAY_WORLD03_AREA119_13_H

/* The world03/area119/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "work/actor.h"
#include "world/area.h"
#include "overlays/area/world03.h"
#include "work/area_spad.h"
#include <rand.h>

#define g_SceneFlags ((void*)g_SceneFlags)

extern u8 D_80146920[];
extern u8 D_801F45C4[];

/* The party position in 16.16 fixed point. */
extern s32 D_80145EC4;
extern s32 D_80145EC8;

void func_801F3324(void);
void func_801F369C(s32 level);
void func_801F3F04(s32 arg0);

#endif

#ifndef OVERLAY_WORLD02_AREA109_13_H
#define OVERLAY_WORLD02_AREA109_13_H

/* The world02/area109/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world02.h"
#include "area/spad.h"

extern u8 D_801F2E90[];

/* The ground height and scene mode of each of the eight variants the three
 * scene flags select, after the flag ids. */
#define g_AreaVariantHeights ((u16*)(D_801F2E90 + 2))
#define g_AreaVariantModes   (D_801F2E90 + 0xF)

s32 func_801F2D04(void);

#endif

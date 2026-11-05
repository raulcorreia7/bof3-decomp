#ifndef OVERLAY_WORLD04_AREA199_13_H
#define OVERLAY_WORLD04_AREA199_13_H

/* The world04/area199/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world04.h"
#include "work/area_spad.h"

/* The scratchpad work row the update passes read. */

/* The map-click frame word the scroll step subtracts from. */

/* The image's palette and cell tables. */
extern u8       D_801F44B4[];
/* The step handler bank. */
extern Callback D_801F44B8[];
extern u8       D_801F54D0[];
extern s8       D_801F54D2;
extern s8       D_801F54D5;

void func_801F2E14(void);
/* The image's step passes. */
void func_801F3398(void);
void func_801F400C(void);

#endif

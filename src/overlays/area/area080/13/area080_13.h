#ifndef OVERLAY_WORLD02_AREA080_13_H
#define OVERLAY_WORLD02_AREA080_13_H

/* The world02/area080/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world02.h"
#include "area/spad.h"

extern u8        D_801F3DAC[];
extern u16       D_801F4494[];
extern u16       D_801F4498[];
extern u16       D_801F449C[];
extern AreaRing* D_801F44A0;
extern s8*       D_801F44A4;

/* func_801F30B0 */
void Area_ProjectRing(AreaRing* ring);
void func_801F31A0(s32 arg0);
void func_801F3834(void);
void func_801F3870(void);

void func_801F395C(void);

#endif

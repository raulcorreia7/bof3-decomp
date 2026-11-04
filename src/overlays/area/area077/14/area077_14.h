#ifndef OVERLAY_WORLD02_AREA077_14_H
#define OVERLAY_WORLD02_AREA077_14_H

/* The world02/area077/14 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world02.h"

#include "shared/WorldSpin.h"

#define AREA_SPIN_PRIM_ORDER 1

#define AREA_SPIN_RADIUS     32
#define AREA_SPIN_PITCH      RANDOM_MASK(0x3FF)
#define AREA_SPIN_SCALE_MASK 0xf
#define AREA_SPIN_SCALE_BASE 1
#define AREA_SPIN_FADE       0

extern u8  D_801F6250[];
extern u8  D_801F62EC[];
extern u16 D_801F6B1C[];
extern u8  D_801F6B28[];
extern u8  D_801F6B30[];
extern u8  D_801F6B38[];
extern u8  D_801F6B40[];
extern u8  D_801F6B48[];
extern u8  D_801F6B50[];
extern u8  D_801F6B58[];

void        Area_ProjectPoint(s32* pos, long* screen_xy);
extern void func_801F54B8(void);
void        func_801F61F0(s32 type);

void func_801F529C(s32, s32, s32, s32);

#endif

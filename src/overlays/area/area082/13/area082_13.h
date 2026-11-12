#ifndef OVERLAY_WORLD02_AREA082_13_H
#define OVERLAY_WORLD02_AREA082_13_H

/* The world02/area082/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world02.h"
#include "area/spad.h"
#include "shared/AreaSpark.h"

extern SVECTOR  D_1F800014[];
extern u8       D_801F5734[];
extern Callback D_801F576C[];

void func_801F3500(void);
u8   func_801F3AAC(void);
void func_801F4430(void);
void func_801F5388(s32 arg0);

void func_801F5428(s32 arg0);

extern Callback D_801F57D0[];

extern u8 D_80145EED[3];

void func_801F387C(AreaSpark* spark);

void func_801F393C(void);
void func_801F2F50(Point3DL* pos, s16 a, s16 b, u16 c, s32 d, s32 e);
void func_801F46C8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

#endif

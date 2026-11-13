#ifndef OVERLAY_WORLD03_AREA132_13_H
#define OVERLAY_WORLD03_AREA132_13_H

/* The world03/area132/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "sys/actor.h"
#include "overlays/area/world03.h"
#include "area/spad.h"

extern u8       D_801F3DD8[];
extern Callback D_801F3DE4[];
extern Callback D_801F3DEC[];
extern Callback D_801F3DF8[];
extern Callback D_801F3E00[];
extern u8*      D_801F4A88;

/* The effect row's draw and step; the update passes the row it advances. */
void func_801F3560(u8* effect);

void func_801F37A4(u8* effect);
u8*  func_801F3800(void);
u8   func_801F38B0(void);

void func_801F3268(void);

#endif

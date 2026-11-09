#ifndef OVERLAY_WORLD03_AREA117_13_H
#define OVERLAY_WORLD03_AREA117_13_H

/* The world03/area117/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world03.h"
#include "area/spad.h"

/* The event-flag table the step checks. */
extern u8  D_80144ED0[];
/* The party position in 16.16 fixed point. */
extern u16 D_801F55D8[];
extern u16 D_801F55E4[];
extern u8  D_801F463C[];
extern u8  D_801F4640[];
extern u8  D_801F558C[];
/* The x/y byte pairs of the cell table indexed by the actor param. */
extern u8  D_801F4658[];
extern u8  D_801F4659[];

void func_801F3884(s32, s32);
void func_801F34C8(void);
void func_801F364C(void);

/* The variant byte the cancel path stores in the game-overlay state. */
#define AREA_RESET_VARIANT 0x1C

/* The game-overlay state bytes the cancel path resets. */

void func_801F2E08(void);

void func_801F3AF8(void);

#endif

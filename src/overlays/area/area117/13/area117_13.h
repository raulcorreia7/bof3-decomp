#ifndef OVERLAY_WORLD03_AREA117_13_H
#define OVERLAY_WORLD03_AREA117_13_H

/* The world03/area117/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/worlds/world03.h"
#include "area/spad.h"

/* The event-flag table the step checks. */
extern u8  D_80144ED0[];
extern u8  D_801F463C[];
extern u8  D_801F4640[];
/* The x/y byte pairs of the cell table indexed by the actor param. */
extern u8  D_801F4658[];
extern u8  D_801F4659[];
extern u8  D_801F558C[];
/* The facing byte at +4 and the walk-flag byte at +5 of the record D_801F558C
 * indexes. */
extern u8  D_801F5590[];
extern u8  D_801F5591[];
/* The party position in 16.16 fixed point. */
extern u16 D_801F55D8[];
extern u16 D_801F55E4[];
/* The trigger cells the area entry step tests: x, y, facing and the flag it toggles. */
extern u8  D_801F55F0[];
extern u8  D_801F55F1[];
extern u8  D_801F55F2[];
extern u8  D_801F55F3[];

void func_801F3884(s32, s32);
void func_801F34C8(void);
void func_801F364C(void);
s32  func_801F4534(s32 x, s32 y);

/* The variant byte the cancel path stores in the game-overlay state. */
#define AREA_RESET_VARIANT 0x1C

/* The game-overlay state bytes the cancel path resets. */

void func_801F2E08(void);

void func_801F3AF8(void);

u8 func_801F4110(u8 member);

#endif

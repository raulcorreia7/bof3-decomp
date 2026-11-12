#ifndef OVERLAY_WORLD04_AREA170_13_H
#define OVERLAY_WORLD04_AREA170_13_H

/* The world04/area170/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world04.h"
#include "area/spad.h"

/* The work origin offset, step and threshold this overlay advances. */
#define AREA_ORIGIN_OFFSET       0x30
#define ACTOR_SCREEN_X_STEP      0x10
#define ACTOR_SCREEN_X_THRESHOLD 0xC0

/* The scratchpad cell holding this mode's work pointer. */

/* The overlay's flag word. */

/* The game-overlay state bytes the request writes. */

/* The shared game work word the flag mask sets. */

/* The party position in 16.16 fixed point. */
/* The payload includes the per-state handler tables. */
extern u8 D_801F57BC[];
extern u8 D_801F5990[];
extern u8 D_801F64B8[];

extern void func_801F3994(void);

s32  Item_Add(s32 category, s32 item, s32 amount, s32 unused);
void func_801F3594(s16 x0, s16 y0, u16 x1, u16 y1, u16 x2, u16 y2, u16 x3, u16 y3, u8 r, u8 g, u8 b, u8 semi_trans);
void func_801F3698(s16 x0, s16 y0, s16 x1, s16 y1, u16 x2, u16 y2, u8 r, u8 g, u8 b, u8 semi_trans);
void func_801F3774(s16 x0, s16 y0, s16 x1, s16 y1, u8 r, u8 g, u8 b, u8 semi_trans);
void func_801F4640(s32 arg0);

#endif

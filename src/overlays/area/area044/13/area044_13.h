#ifndef OVERLAY_WORLD01_AREA044_13_H
#define OVERLAY_WORLD01_AREA044_13_H

/* The world01/area044/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/worlds/world01.h"

/* The first cell pair table: entry n's x at byte 2n and its y at 2n+1. */
extern u8 D_801F3FB4[];
/* The second cell pair table: entry n's x at byte n and its y at n+1. */
extern u8 D_801F3FBC[];

/* The trigger table: the cell pair, the facing and the SE id of each five-byte slot. */
extern u8 D_801F3FC4[];
extern u8 D_801F3FC5[];
extern u8 D_801F3FC6[];
extern u8 D_801F3FC7[];
extern u8 D_801F3FC8[];

void func_801F2DF4(void);
void func_801F318C(u8 facing, u8 actor_index);
s32  func_801F33A8(s32 x, s32 y);

#endif

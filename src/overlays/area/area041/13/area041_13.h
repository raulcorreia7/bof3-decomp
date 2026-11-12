#ifndef OVERLAY_WORLD01_AREA041_13_H
#define OVERLAY_WORLD01_AREA041_13_H

/* The world01/area041/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world01.h"
#include "area/spad.h"

extern u8 D_80144EA0[];

void func_801F2EFC(void);
void func_801F3064(void);

extern s8  D_80146865;
extern u8  D_801F42C8[];
extern u8  D_801F42CC[];
extern u8  D_801F42D0[];
extern u8  D_801F42DC[];
extern u8  D_801F42EC[];
extern u8  D_801F4308[];
extern u8  D_801F5651[];
extern u16 D_801F5678[];
extern u8  D_801F567C[];

void func_801F387C(s32);

/* The game-overlay state bytes the cancel path resets. */

s32  Item_Count(s32 category, s32 item_id, s32 mode);
s32  Item_Add(s32 category, s32 item_id, s32 count, s32 mode);
void func_801F4118(void);

#endif

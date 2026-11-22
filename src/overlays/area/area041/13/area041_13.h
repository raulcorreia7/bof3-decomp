#ifndef OVERLAY_WORLD01_AREA041_13_H
#define OVERLAY_WORLD01_AREA041_13_H

/* The world01/area041/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/worlds/world01.h"

extern u8 D_80144EA0[];

void func_801F2EFC(void);
void func_801F3064(void);

extern u8  D_801F42C8[];
extern u8  D_801F42CC[];
extern u8  D_801F42D0[];
extern u32 D_801F42D4[];
extern u8  D_801F42DC[];
extern u8  D_801F42EC[];
extern u8  D_801F4308[];
extern u8  D_801F4334[];
extern u8  D_801F4344[];
extern s8  D_801F4354[];
/* The six-row sprite's cell pairs: row n's x is the byte at 2n and its y the byte one after. */
extern u8  D_801F4364[];
/* The six sprite words' low bytes, one per row. */
extern u8  D_801F4370[];
extern u8  D_801F5651[];
extern u16 D_801F5678[];
extern u8  D_801F567C[];

void func_801F387C(s32 angle);

/* The game-overlay state bytes the cancel path resets. */

void func_801F4118(void);

#endif

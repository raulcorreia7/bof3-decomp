#ifndef OVERLAY_WORLD01_AREA041_13_H
#define OVERLAY_WORLD01_AREA041_13_H

/* The world01/area041/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world01.h"
#include "work/area_spad.h"

void Area_SetCellCode(s16 column, s16 row, u8 code);

extern u8 D_80144EA0[];

void func_801F2EFC(void);
void func_801F3064(void);

extern u8 D_801F42DC[];
extern u8 D_801F42EC[];
extern u8 D_801F5651[];
extern u8 D_801F567C[];

/* The game-overlay state bytes the cancel path resets. */

#endif

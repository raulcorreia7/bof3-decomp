#ifndef OVERLAY_BOSS_BOSS030_16_H
#define OVERLAY_BOSS_BOSS030_16_H

/* The boss/boss030/16 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/boss/boss.h"

extern u8       D_800C1AB4[];
extern u8       D_800C1AC0[];
extern u16      D_800C1ACC[];
extern u16      D_800C1AD4[];
extern Callback D_800C1B0C[];
extern Callback D_800C1B18[];
extern Callback D_800C1B48[];

void func_800C18A0(s32 mode);
void func_800C198C(s32 mode);

#endif

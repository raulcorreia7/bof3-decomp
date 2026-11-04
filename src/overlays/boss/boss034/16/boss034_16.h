#ifndef OVERLAY_BOSS_BOSS034_16_H
#define OVERLAY_BOSS_BOSS034_16_H

/* The boss/boss034/16 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/boss/boss.h"

extern u8       D_800C26B8[];
extern u8       D_800C2778;
extern u8       D_80181B14;
extern u16      D_800C26C4[];
extern Callback D_800C2714[];
extern Callback D_800C2730[];
extern Callback D_800C273C[];
extern Callback D_800C276C[];

void func_800C1D60(s32 mode);
u8   func_800C1F30(u32 mode);
void func_800C20A8(void);
void func_800C22D0(void);

#endif

#ifndef OVERLAY_BOSS_BOSS035_16_H
#define OVERLAY_BOSS_BOSS035_16_H

/* The boss/boss035/16 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/boss/boss.h"

extern u8       D_800C1D04[];
extern u8       D_800C1D10[];
extern u16      D_800C1D1C[];
extern u16      D_800C1D24[];
extern Callback D_800C1D68[];
extern Callback D_800C1D98[];
extern Callback D_800C1DA4[];
extern Callback D_800C1DD4[];

void func_800C19F8(s32 mode);
void func_800C1AFC(s32 mode);

#endif

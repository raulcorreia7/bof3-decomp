#ifndef OVERLAY_BOSS_BOSS023_16_H
#define OVERLAY_BOSS_BOSS023_16_H

/* The boss/boss023/16 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/boss/boss.h"

extern u8       D_800C1A40[];
extern u8       D_800C1A4C[];
extern u16      D_800C1A58[];
extern u16      D_800C1A60[];
extern u16      D_800C1A68[];
extern Callback D_800C1AA0[];

/* The mode handler sets the image installs into the battle hooks; the
 * addresses are in [emi/boss/boss023/16] of config/symbols.toml. */

void func_800C1934(s32 mode);

#endif

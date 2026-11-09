#ifndef OVERLAY_BOSS_BOSS012_16_H
#define OVERLAY_BOSS_BOSS012_16_H

/* The boss/boss012/16 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/boss/boss.h"

extern u8       D_800C1E14[];
extern u16      D_800C1E20[];
extern u8       D_800C1E64[];
extern Callback D_800C1E74[];
extern Callback D_800C1EA4[];
extern Callback D_800C1EBC[];
extern Callback D_800C1ECC[];

/* The mode handler sets the image installs into the battle hooks; the
 * addresses are in [emi/boss/boss012/16] of config/symbols.toml. */

void func_800C1CD8(s32 mode);

#endif

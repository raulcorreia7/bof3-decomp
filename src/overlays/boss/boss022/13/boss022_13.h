#ifndef OVERLAY_BOSS_BOSS022_13_H
#define OVERLAY_BOSS_BOSS022_13_H

/* The boss/boss022/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/boss/boss.h"

/* The mode handler sets the image installs into the battle hooks; the
 * addresses are in [emi/boss/boss022/13] of config/symbols.toml. */

extern u8       D_800C1B18[];
extern u16      D_800C1B24[];
extern Callback D_800C1B2C[];
extern Callback D_800C1B5C[];

void func_800C19B8(s32 mode);

#endif

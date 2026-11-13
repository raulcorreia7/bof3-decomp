#ifndef OVERLAY_BOSS_BOSS021_16_H
#define OVERLAY_BOSS_BOSS021_16_H

/* The boss/boss021/16 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/boss/boss.h"

extern u8       D_800C1CB0[];
extern u8       D_800C1CBC[];
extern u16      D_800C1CC8[];
extern u16      D_800C1CD0[];
extern Callback D_800C1CD8[];
extern Callback D_800C1D08[];
extern Callback D_800C1D20[];

/* The mode handler sets the image installs into the battle hooks; the
 * addresses are in [emi/boss/boss021/16] of config/symbols.toml. */

/* The enemy-work mode dispatch each installer publishes at unk_E4. */
void func_800C198C(s32 mode);

#endif

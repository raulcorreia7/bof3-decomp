#ifndef OVERLAY_BOSS_BOSS007_16_H
#define OVERLAY_BOSS_BOSS007_16_H

/* The boss/boss007/16 overlay: one file per split function and its data. */

#include "overlays/boss/boss.h"

extern u8       D_800C1D78[];
extern u8       D_800C1D84[];
extern u16      D_800C1D90[];
extern u16      D_800C1D98[];
extern Callback D_800C1DA0[];
extern Callback D_800C1DD0[];
extern Callback D_800C1DDC[];
extern Callback D_800C1E0C[];
/* The battle cell base at 0x80146390 is declared by src/overlays/battle/battle.h. */

/* The mode handler sets the image installs into the battle hooks. */

/* The enemy-work mode dispatch each installer publishes at unk_E4. */
void func_800C18BC(s32 mode);
void func_800C19B4(s32 mode);

#endif

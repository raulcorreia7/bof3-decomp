#ifndef OVERLAY_BOSS_BOSS015_16_H
#define OVERLAY_BOSS_BOSS015_16_H

/* The boss/boss015/16 overlay: one file per split function and its data. */

#include "overlays/boss/boss.h"

extern u8       D_800C199C[];
extern u16      D_800C19A8[];
extern Callback D_800C19B0[];
extern Callback D_800C19E0[];

/* The mode handler sets the image installs into the battle hooks. */

/* The enemy-work mode dispatch each installer publishes at unk_E4. */
void func_800C18A0(s32 mode);

#endif

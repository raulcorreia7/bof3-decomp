#ifndef OVERLAY_BOSS_BOSS017_16_H
#define OVERLAY_BOSS_BOSS017_16_H

/* The boss/boss017/16 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/boss/boss.h"

extern u16      D_800C1A94[];
extern Callback D_800C1AAC[];
extern Callback D_800C1AF4[];

/* The mode handler sets the image installs into the battle hooks; the
 * addresses are in [emi/boss/boss017/16] of config/symbols.toml. */

/* The enemy-work mode dispatch each installer publishes at unk_E4. */
void func_800C1964(s32 mode);

#endif

#ifndef OVERLAY_BOSS_BOSS024_16_H
#define OVERLAY_BOSS_BOSS024_16_H

/* The boss/boss024/16 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/boss/boss.h"

#define BOSS_ENEMY_SCRIPT    D_800C1B44
#define BOSS_ENEMY_STEP_DATA D_800C1B50

extern u8       D_800C1B44[];
extern u16      D_800C1B50[];
extern Callback D_800C1B58[];
extern Callback D_800C1B88[];
extern Callback D_800C1B94[];
extern Callback D_800C1BC4[];

/* The mode handler sets the image installs into the battle hooks; the
 * addresses are in [emi/boss/boss024/16] of config/symbols.toml. */

/* The enemy-work mode dispatch each installer publishes at unk_E4. */
void func_800C18A0(s32 mode);

#endif

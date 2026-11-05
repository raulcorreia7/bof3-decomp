#ifndef OVERLAY_BOSS_BOSS014_16_H
#define OVERLAY_BOSS_BOSS014_16_H

/* The boss/boss014/16 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/boss/boss.h"

#define BOSS_ENEMY_SCRIPT    D_800C1B28
#define BOSS_ENEMY_STEP_DATA D_800C1B3C

extern u8       D_800C1B28[];
extern u16      D_800C1B34[];
extern u16      D_800C1B3C[];
extern Callback D_800C1B44[];
extern Callback D_800C1B80[];
extern Callback D_800C1BB0[];

/* The mode handler sets the image installs into the battle hooks; the
 * addresses are in [emi/boss/boss014/16] of config/symbols.toml. */

/* The enemy-work mode dispatch each installer publishes at unk_E4. */
void func_800C18A0(s32 mode);

#endif

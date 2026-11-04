#ifndef OVERLAY_BOSS_BOSS050_16_H
#define OVERLAY_BOSS_BOSS050_16_H

/* The boss/boss050/16 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/boss/boss.h"
#include "battle/ram.h"

extern Callback D_800C1804[];
extern u8       D_800C1B34[];
extern u16      D_800C1B40[];
extern Callback D_800C1B4C[];
extern Callback D_800C1B7C[];

void func_800C18B8(s32 mode);
extern BattleEffect* D_801EC2E0;

#endif

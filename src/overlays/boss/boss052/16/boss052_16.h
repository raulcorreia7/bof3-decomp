#ifndef OVERLAY_BOSS_BOSS052_16_H
#define OVERLAY_BOSS_BOSS052_16_H

/* The boss/boss052/16 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/boss/boss.h"
#include "overlays/battle/battle.h"

#define g_CurrentActor ((void*)g_CurrentActor)

extern Callback D_800C1804[];
extern u8       D_800C1F3C[];
extern u16      D_800C1F48[];
extern Callback D_800C1F50[];
extern Callback D_800C1F80[];
extern Callback D_800C1F98[];
extern Callback D_800C1FA4[];
extern s8       D_80146875;

void func_800C1984(s32 mode);

#endif

#ifndef OVERLAY_BOSS_BOSS033_16_H
#define OVERLAY_BOSS_BOSS033_16_H

/* The boss/boss033/16 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/boss/boss.h"
#include "overlays/battle/battle.h"

extern volatile u8 g_BattleActingBattler;
extern s32         D_80145EC4;
extern s8          D_80146875;
extern u8          D_800C2744[];
extern u16         D_800C2750[];
extern Callback    D_800C275C[];
extern Callback    D_800C278C[];
extern Callback    D_800C2798[];
extern Callback    D_800C27A0[];
extern Callback    D_800C27AC[];
extern Callback    D_800C27B4[];
extern Callback    D_800C27D0[];

/* The battle target calls the battle image defines. */
s32 func_800AF2B4(void* target, s32 step);
s32 func_800AF5FC(void* target, u32 extent);

void func_800C1CA4(s32 mode);

#endif

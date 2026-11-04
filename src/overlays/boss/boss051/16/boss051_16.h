#ifndef OVERLAY_BOSS_BOSS051_16_H
#define OVERLAY_BOSS_BOSS051_16_H

/* The boss/boss051/16 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/boss/boss.h"

/* The scratchpad work area is a PartyBattler record in this image. */
#define g_SpadWork ((PartyBattler*)g_SpadWork)

extern Callback D_800C1804[];
extern u8       D_800C1DB0[];
extern u16      D_800C1DBC[];
extern Callback D_800C1DC4[];
extern Callback D_800C1DF4[];
extern Callback D_800C1DFC[];

void func_800C19C4(s32 mode);

#endif

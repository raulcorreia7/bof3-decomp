#ifndef OVERLAY_BOSS_BOSS036_16_H
#define OVERLAY_BOSS_BOSS036_16_H

/* The boss/boss036/16 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/boss/boss.h"
#include "overlays/battle/battle.h"

/* The scratchpad work area is a PartyMember record in this image. */
#define g_Task ((PartyMember*)g_Task)

extern Callback D_800C1804[];
extern u8       D_800C2020[];
extern u16      D_800C202C[];
extern Callback D_800C2034[];
extern Callback D_800C2064[];
extern Callback D_800C206C[];
extern Callback D_800C2074[];
extern Callback D_800C2080[];
extern Callback D_800C20B0[];
extern Callback D_800C20BC[];

void func_800C1B24(s32 mode);
void func_800C1D40(s32 mode);

#endif

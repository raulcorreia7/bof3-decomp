#ifndef OVERLAY_BOSS_BOSS032_16_H
#define OVERLAY_BOSS_BOSS032_16_H

/* The boss/boss032/16 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/boss/boss.h"

/* The scratchpad work area is a PartyMember record in this image. */
#define g_Task ((PartyMember*)g_Task)

extern s8 D_80146875;

#define g_CurrentActor ((void*)g_CurrentActor)

extern u8       D_800C1C2C[];
extern u16      D_800C1C38[];
extern Callback D_800C1C40[];
extern Callback D_800C1C70[];
extern Callback D_800C1C88[];

#endif

#ifndef OVERLAY_BOSS_BOSS025_13_H
#define OVERLAY_BOSS_BOSS025_13_H

/* The boss/boss025/13 overlay: one file per split function and its data. */

#include "overlays/boss/boss.h"

/* The scratchpad work area is a PartyMember record in this image. */
#define g_Task ((PartyMember*)g_Task)

extern u8          D_800C3180[];
extern u16         D_800C3194[];
extern Callback    D_800C319C[];
extern Callback    D_800C31CC[];
extern Callback    D_800C31E4[];
extern Callback    D_800C31F0[];
extern Callback    D_800C3220[];
extern Callback    D_800C3238[];
extern Callback    D_800C3244[];
extern Callback    D_800C3274[];
extern Callback    D_800C327C[];
extern Callback    D_800C3294[];
extern Callback    D_800C32A0[];
extern u8          D_800C32B4;
extern u8          D_800C32B8;
extern u16         D_80145F18;
/* The word at g_Battle.scroll_dir. */
extern u32         D_801462EC;
extern volatile u8 D_80146322;
extern s8          D_80146875;
extern u8          D_80148603;
extern u8          D_801FE4E4;
extern u32         D_801FE4E8;
extern u8          D_801FE4EC[];
extern u8          D_801FE4EF;
extern u32         D_801FE4F0;

void func_800C20F0(s32 mode);

#endif

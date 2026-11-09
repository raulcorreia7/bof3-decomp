#ifndef OVERLAY_BOSS_BOSS004_13_H
#define OVERLAY_BOSS_BOSS004_13_H

/* The boss/boss004/13 overlay: one file per split function and its data. */

#include "overlays/boss/boss.h"

/* The scratchpad work area is a PartyMember record in this image. */
#define g_Task ((PartyMember*)g_Task)

extern u8       D_800C2720[];
extern u8       D_800C272C;
extern u16      D_800C2738[];
extern Callback D_800C2740[];
extern Callback D_800C2770[];
extern Callback D_800C2788[];
extern Callback D_800C2794[];

/* The mode handler sets the image installs into the battle hooks. */

/* The enemy-work mode dispatch each installer publishes at unk_E4. */
void func_800C1BBC(s32 mode);

#endif

#ifndef OVERLAY_BATTLE_BATL_OVR_00_H
#define OVERLAY_BATTLE_BATL_OVR_00_H

#include "overlays/battle/battle.h"

/* FAKE: g_Battle.ui_step as a global of its own; the sites that use it match only with a separate symbol. */
extern u8       g_BattleUIStep;
extern u16      D_801463B0;
extern void     func_801EF180(s32 arg);
extern void     func_801EF3B4(s32 shade);
extern void     func_801EF47C(s32 x);
extern Callback D_801EF5F8[];

/* The party's start screen positions: one 24-byte row per party size, three (x, y) s32 pairs
 * copied to each member's unk_2E and unk_30. */
extern s32 D_801EF60C[3][3][2];

#endif

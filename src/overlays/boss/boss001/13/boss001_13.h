#ifndef OVERLAY_BOSS_BOSS001_13_H
#define OVERLAY_BOSS_BOSS001_13_H

/* The boss/boss001/13 overlay: one file per split function and its data. */

#include "overlays/boss/boss.h"

/* The scratchpad work area is a PartyMember record in this image. */
#define g_Task ((PartyMember*)g_Task)

extern u8           D_800C217C[];
extern u8           D_800C2188;
extern u8           D_800C2194[];
extern u8           D_800C21A0;
extern u16          D_800C21AC[];
extern u16          D_800C21B4[];
extern Callback     D_800C21EC[];
extern Callback     D_800C2204[];
extern Callback     D_800C2210[];
extern Callback     D_800C221C[];
extern Callback     D_800C224C[];
extern Callback     D_800C2264[];
extern Callback     D_800C2270[];
/* Battle RAM cell cleared by the mode start. */
extern volatile u16 D_801463BE;
/* D_801EB630 */
extern EnemyBattler g_BattleEnemyBattlers[];

/* The three battle hooks the image installs; the addresses are in [emi/boss/boss001/13] of config/symbols.toml. */

/* The enemy-work mode dispatch each installer publishes at unk_E4. */
void func_800C1E00(s32 mode);

#endif

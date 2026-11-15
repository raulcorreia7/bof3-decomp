#ifndef OVERLAY_BOSS_BOSS051_16_H
#define OVERLAY_BOSS_BOSS051_16_H

/* The boss/boss051/16 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/boss/boss.h"

/* The scratchpad work area is a PartyMember record in this image. */
#define g_Task ((PartyMember*)g_Task)

#include "game/enemy.h"
#include "overlays/battle/battle.h"

extern Callback D_800C1804[];
/* D_800C1DB0 */
extern u8       g_BossEnemyScript[];
/* D_800C1DBC */
extern u16      g_BossEnemyActions[];
extern Callback D_800C1DC4[];
extern Callback D_800C1DF4[];
extern Callback D_800C1DFC[];

/* func_800C19C4 */
void Boss_EnemyScriptMode(s32 mode);

#endif

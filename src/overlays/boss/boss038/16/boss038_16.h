#ifndef OVERLAY_BOSS_BOSS038_16_H
#define OVERLAY_BOSS_BOSS038_16_H

/* The boss/boss038/16 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/boss/boss.h"

/* The scratchpad work area is a PartyMember record in this image. */
#define g_Task ((PartyMember*)g_Task)

/* D_800C1C10 */
extern u8       g_BossEnemyScript[];
/* D_800C1C1C */
extern u16      g_BossEnemyActions[];
extern Callback D_800C1C24[];
extern Callback D_800C1C54[];
extern Callback D_800C1C60[];
extern Callback D_800C1C90[];

void func_800C18EC(u8 index);

/* func_800C19E4 */
void Boss_EnemyScriptMode(s32 mode);

#endif
